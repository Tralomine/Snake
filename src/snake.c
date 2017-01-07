#include <stdlib.h>
#include "../include/SDL/SDL.h"
#include "../include/SDL/SDL_image.h"

#include "const.h"
#include "display.h"
#include "game.h"

#include "snake.h"

///affiche le snake sur l'écran
void displaySnake(SDL_Surface* screen, Snake* snake, int numero)
{
    LargeSprite snakeHead, snakeTail, snakeBody;

    if(numero==1){
        snakeHead = setLargeSprite("texture/snake_head.png", 4, 0);
        snakeBody = setLargeSprite("texture/snake_body.png", 8, 0);
        snakeTail = setLargeSprite("texture/snake_tail.png", 4, 0);
    }               //on prend une texture différente pour le 2eme serpent en multi
    if(numero==2){
        snakeHead = setLargeSprite("texture/snake_head2.png", 4, 0);
        snakeBody = setLargeSprite("texture/snake_body2.png", 8, 0);
        snakeTail = setLargeSprite("texture/snake_tail2.png", 4, 0);
    }

    switch(snake->dir){
        case HAUT:
            changeLargeSprite(&snakeHead, 0);
            break;
        case BAS:
            changeLargeSprite(&snakeHead, 2);
            break;
        case GAUCHE:
            changeLargeSprite(&snakeHead, 3);
            break;
        case DROITE:
            changeLargeSprite(&snakeHead, 1);
            break;
    }
    displayLargeSprite(screen, &snakeHead, snake->corp[0].x*TAILLESPRITE, snake->corp[0].y*TAILLESPRITE); //la tête
    int i;
    for(i=1;i<snake->taille-1;i++){
        if(snake->corp[i].y == snake->corp[i-1].y-1){
            if(snake->corp[i].y == snake->corp[i+1].y+1)      //en fonction de la position des segments precedents
                changeLargeSprite(&snakeBody, 0);               //et suivants, on n'affiche pas les mêmes sprites
            if(snake->corp[i].x == snake->corp[i+1].x-1)      //pour que le serpent reste en un seul morceau
                changeLargeSprite(&snakeBody, 7);               //et qu'il reste coherent sur toute la longueur
            if(snake->corp[i].x == snake->corp[i+1].x+1)
                changeLargeSprite(&snakeBody, 8);}
        if(snake->corp[i].y == snake->corp[i-1].y+1){
            if(snake->corp[i].y == snake->corp[i+1].y-1)
                changeLargeSprite(&snakeBody, 2);
            if(snake->corp[i].x == snake->corp[i+1].x-1)
                changeLargeSprite(&snakeBody, 10);
            if(snake->corp[i].x == snake->corp[i+1].x+1)
                changeLargeSprite(&snakeBody, 5);}
        if(snake->corp[i].x == snake->corp[i-1].x-1){
            if(snake->corp[i].x == snake->corp[i+1].x+1)
                changeLargeSprite(&snakeBody, 3);
            if(snake->corp[i].y == snake->corp[i+1].y-1)
                changeLargeSprite(&snakeBody, 11);
            if(snake->corp[i].y == snake->corp[i+1].y+1)
                changeLargeSprite(&snakeBody, 6);}
        if(snake->corp[i].x == snake->corp[i-1].x+1){
            if(snake->corp[i].x == snake->corp[i+1].x-1)
                changeLargeSprite(&snakeBody, 1);
            if(snake->corp[i].y == snake->corp[i+1].y-1)
                changeLargeSprite(&snakeBody, 4);
            if(snake->corp[i].y == snake->corp[i+1].y+1)
                changeLargeSprite(&snakeBody, 9);}

        displayLargeSprite(screen, &snakeBody, snake->corp[i].x*TAILLESPRITE, snake->corp[i].y*TAILLESPRITE); //le corp entre la queue et la tête
    }

    if(snake->corp[snake->taille-1].y == snake->corp[snake->taille-2].y+1)
        changeLargeSprite(&snakeTail, 0);
    if(snake->corp[snake->taille-1].y == snake->corp[snake->taille-2].y-1)
        changeLargeSprite(&snakeTail, 2);
    if(snake->corp[snake->taille-1].x == snake->corp[snake->taille-2].x+1)
        changeLargeSprite(&snakeTail, 1);
    if(snake->corp[snake->taille-1].x == snake->corp[snake->taille-2].x-1)
        changeLargeSprite(&snakeTail, 3);

    displayLargeSprite(screen, &snakeTail, snake->corp[snake->taille-1].x*TAILLESPRITE, snake->corp[snake->taille-1].y*TAILLESPRITE); //la queue

    destroyLargeSprite(&snakeHead);
    destroyLargeSprite(&snakeBody);
    destroyLargeSprite(&snakeTail);
}

///calcule le déplacement et les collisions des 2 serpents
void deplacement_snake(void* temp)
{
    Game* game = (Game*)temp;       //on converti directement le pointeur sur vide en pointeur sur Game
    int i, j, k, nbr_serpents = 1;

    if(game->multiplayer == TRUE)
        nbr_serpents = 2;

    for(i=0;i<nbr_serpents;i++){

        int inc_x=0, inc_y=0;

        //les serpents changent de direction
        game->snake[i].dir = game->snake[i].nextdir;

        //on agrandit leur taille si ils doivent grandir
        if(game->snake[i].growWait>0){
            game->snake[i].taille++;
            game->snake[i].growWait--;
        }

        if(game->snake[i].dir == HAUT)
            inc_y++;
        if(game->snake[i].dir == BAS)
            inc_y--;
        if(game->snake[i].dir == DROITE)
            inc_x++;
        if(game->snake[i].dir == GAUCHE)
            inc_x--;

        //------DEPLACEMENT_SERPENT------
        //on décale toutes les cases d'un vers l'avant
        for(j=game->snake[i].taille-1;j>0;j--){
            game->snake[i].corp[j] = game->snake[i].corp[j-1];
        }
        //on decale sa tête
        game->snake[i].corp[0].x+=inc_x;
        game->snake[i].corp[0].y+=inc_y;

        //depassement du cadre
        if(game->snake[i].corp[0].x < 0)
            game->snake[i].corp[0].x = TAILLEX-1;
        if(game->snake[i].corp[0].x > TAILLEX-1)
            game->snake[i].corp[0].x = 0;
        if(game->snake[i].corp[0].y < 0)
            game->snake[i].corp[0].y = TAILLEY-1;
        if(game->snake[i].corp[0].y > TAILLEY-1)
            game->snake[i].corp[0].y = 0;

        //------COLLISION------
        //on remet la collision a 0
        game->snake[i].collision = 0;

        //collision avec les murs
        if(game->levelMap[game->snake[i].corp[0].x][game->snake[i].corp[0].y] == MUR)
            game->snake[i].collision = 1;

        //collision avec lui-même
        for(j=3;j<=game->snake[i].taille-1;j++){ //on ne peux pas manger avant le 3eme segment, ni la queue, parce qu'elle bougera au prochain coup
            if(game->snake[i].corp[0].x == game->snake[i].corp[j].x && game->snake[i].corp[0].y == game->snake[i].corp[j].y)
                game->snake[i].collision = 1;  //on perd si tete collision soi meme
        }

        //collision avec les autres serpents
        if(game->multiplayer == TRUE){
            ///on regarde quand les serpents se touchent entre eux
            for(k=0;k<nbr_serpents;k++){
                if(i!=k)    //on regarde si on touche les AUTRES serpents
                    for(j=0;j<game->snake[i].taille;j++){       //sur n'importe quel endroit du corp
                        if(game->snake[i].corp[0].x == game->snake[k].corp[j].x && game->snake[i].corp[0].y == game->snake[k].corp[j].y)
                            game->snake[i].collision = 1;
                }
            }
        }

        //fruits
        if(game->levelMap[game->snake[i].corp[0].x][game->snake[i].corp[0].y] == FRUIT){
            game->snake[i].collision = 2;        //on lui dit qu'il a croisé un fruit
            game->levelMap[game->snake[i].corp[0].x][game->snake[i].corp[0].y] = VIDE; //on eneve le fruit
        }
    }
}
