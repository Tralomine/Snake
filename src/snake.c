#include <stdlib.h>
#include "../include/SDL/SDL.h"
#include "../include/SDL/SDL_image.h"

#include "const.h"
#include "display.h"
#include "game.h"

#include "snake.h"


void displaySnake(SDL_Surface* screen, Snake* snake)
{
    LargeSprite snakeHead, snakeTail, snakeBody;

    setLargeSprite(&snakeHead, "texture/snake_head.png", 4, 0);
    setLargeSprite(&snakeBody, "texture/snake_body.png", 8, 0);
    setLargeSprite(&snakeTail, "texture/snake_tail.png", 4, 0);

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
    displayLargeSprite(screen, &snakeHead, snake->snake[0].x*TAILLESPRITE, snake->snake[0].y*TAILLESPRITE); //la tête
    int i;
    for(i=1;i<snake->taille-1;i++){
        if(snake->snake[i].y == snake->snake[i-1].y-1){
            if(snake->snake[i].y == snake->snake[i+1].y+1)
                changeLargeSprite(&snakeBody, 0);
            if(snake->snake[i].x == snake->snake[i+1].x-1)
                changeLargeSprite(&snakeBody, 7);
            if(snake->snake[i].x == snake->snake[i+1].x+1)
                changeLargeSprite(&snakeBody, 8);
        }
        if(snake->snake[i].y == snake->snake[i-1].y+1){
            if(snake->snake[i].y == snake->snake[i+1].y-1)
                changeLargeSprite(&snakeBody, 2);
            if(snake->snake[i].x == snake->snake[i+1].x-1)
                changeLargeSprite(&snakeBody, 10);
            if(snake->snake[i].x == snake->snake[i+1].x+1)
                changeLargeSprite(&snakeBody, 5);
        }
        if(snake->snake[i].x == snake->snake[i-1].x-1){
            if(snake->snake[i].x == snake->snake[i+1].x+1)
                changeLargeSprite(&snakeBody, 3);
            if(snake->snake[i].y == snake->snake[i+1].y-1)
                changeLargeSprite(&snakeBody, 11);
            if(snake->snake[i].y == snake->snake[i+1].y+1)
                changeLargeSprite(&snakeBody, 6);
        }
        if(snake->snake[i].x == snake->snake[i-1].x+1){
            if(snake->snake[i].x == snake->snake[i+1].x-1)
                changeLargeSprite(&snakeBody, 1);
            if(snake->snake[i].y == snake->snake[i+1].y-1)
                changeLargeSprite(&snakeBody, 4);
            if(snake->snake[i].y == snake->snake[i+1].y+1)
                changeLargeSprite(&snakeBody, 9);
        }

        displayLargeSprite(screen, &snakeBody, snake->snake[i].x*TAILLESPRITE, snake->snake[i].y*TAILLESPRITE); //le corp entre
    }

    if(snake->snake[snake->taille-1].y == snake->snake[snake->taille-2].y+1)
        changeLargeSprite(&snakeTail, 0);
    if(snake->snake[snake->taille-1].y == snake->snake[snake->taille-2].y-1)
        changeLargeSprite(&snakeTail, 2);
    if(snake->snake[snake->taille-1].x == snake->snake[snake->taille-2].x+1)
        changeLargeSprite(&snakeTail, 1);
    if(snake->snake[snake->taille-1].x == snake->snake[snake->taille-2].x-1)
        changeLargeSprite(&snakeTail, 3);

    displayLargeSprite(screen, &snakeTail, snake->snake[snake->taille-1].x*TAILLESPRITE, snake->snake[snake->taille-1].y*TAILLESPRITE); //la queue



    destroyLargeSprite(&snakeHead);
    destroyLargeSprite(&snakeBody);
    destroyLargeSprite(&snakeTail);
}

//fonction de callback pour la SDL
Uint32 deplacement_snake(Uint32 intervalle, void* temp)
{
    Game* game = (Game*)temp;
    game->snake.dir = game->snake.nextdir;
    int inc_x=0, inc_y=0, i;
    game->collision = 0;

    //on agrandit sa taille si il doit grandir
    if(game->snake.growWait>0){
        game->snake.taille++;
        game->snake.growWait--;
    }

    if(game->snake.dir == HAUT)
        inc_y++;
    if(game->snake.dir == BAS)
        inc_y--;
    if(game->snake.dir == DROITE)
        inc_x++;
    if(game->snake.dir == GAUCHE)
        inc_x--;

    //------COLLISION------
    if(game->levelMap[game->snake.snake[0].x+inc_x][game->snake.snake[0].y+inc_y] == MUR)
        game->collision = 1;      //on perd si tete collision mur

    for(i=3;i<=game->snake.taille-2;i++){ //on ne peux pas manger avant le 3eme segment, ni la queue, parce qu'elle bougera au prochain coup
        if(game->snake.snake[0].x+inc_x == game->snake.snake[i].x && game->snake.snake[0].y+inc_y == game->snake.snake[i].y)
            game->collision = 1;  //on perd si tete collision serpent
    }

    //fruits
    if(game->levelMap[game->snake.snake[0].x+inc_x][game->snake.snake[0].y+inc_y] == FRUIT){
        game->collision = 2;        //on lui dit qu'il a croisé un fruit
        game->levelMap[game->snake.snake[0].x+inc_x][game->snake.snake[0].y+inc_y] = VIDE; //on eneve le fruit
    }
    //------COLLISION------

    //------DEPLACEMENT_SERPENT------
    for(i=game->snake.taille-1;i>0;i--){
        game->snake.snake[i] = game->snake.snake[i-1];
    }
    game->snake.snake[0].x+=inc_x;
    game->snake.snake[0].y+=inc_y;

    //depassement du cadre
    if(game->snake.snake[0].x < 0)
        game->snake.snake[0].x = TAILLEX-1;
    if(game->snake.snake[0].x > TAILLEX-1)
        game->snake.snake[0].x = 0;
    if(game->snake.snake[0].y < 0)
        game->snake.snake[0].y = TAILLEY-1;
    if(game->snake.snake[0].y > TAILLEY-1)
        game->snake.snake[0].y = 0;
    //------DEPLACEMENT_SERPENT------

    return intervalle;
}
