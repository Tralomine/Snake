#include <stdlib.h>
#include "../include/SDL/SDL.h"
#include "../include/SDL/SDL_image.h"

#include "display.h"
#include "snake.h"

void displaySnake(SDL_Surface* screen, Snake *snake)
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
    displayLargeSprite(screen, &snakeHead, snake->snake[0].x*TAILLESPRITE, snake->snake[0].y*TAILLESPRITE); //la t�te
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

void displayMap(SDL_Surface* screen, Map levelMap[TAILLEX][TAILLEY])
{
    Sprite wall, fruit, background;
    setSprite(&wall, "texture/brickWall.png");
    setSprite(&fruit, "texture/fruit.png");
    setSprite(&background, "texture/background.png");
    int x, y;

    for(x=0;x<TAILLEX;x++){
        for(y=0;y<TAILLEY;y++){
            displaySprite(screen, &background, x*TAILLESPRITE, y*TAILLESPRITE);
            if(levelMap[x][y]==MUR)
                displaySprite(screen, &wall, x*TAILLESPRITE, y*TAILLESPRITE);
            if(levelMap[x][y]==FRUIT)
                displaySprite(screen, &fruit, x*TAILLESPRITE, y*TAILLESPRITE);
        }
    }
    destroySprite(&wall);
    destroySprite(&fruit);
}

//fonction de callback pour la SDL
Uint32 deplacement_snake(Uint32 intervalle, void* temp)
{
    Game* game = (Game*)temp;
    game->snake.dir = game->snake.nextdir;
    int inc_x=0, inc_y=0, i;
    game->collision = 0;

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
        game->snake.taille++;       //GRANDIT si tete snake collision fruit
        game->collision = 2;        //on lui dit qu'il a crois� un fruit
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

//genere un nouveau fruit sur une case vide
void generation_fruit(Game *game)
{
    int fruit=0, fruit_x, fruit_y;
    int i;
    while(fruit==0){
        fruit_x=rand()%TAILLEX;
        fruit_y=rand()%TAILLEY;
        if(game->levelMap[fruit_x][fruit_y]==VIDE){
            fruit=1;
        }
        for(i=0;i<game->snake.taille;i++){
            if(game->snake.snake[i].x == fruit_x &&game->snake.snake[i].y == fruit_y){
                fruit = 0;
                break;
            }
        }
    }
    game->levelMap[fruit_x][fruit_y]=FRUIT;
}

void setupGame(Game* game)
{
    int x, y, dir;
    //dir = rand()%4;


    game->snake.snake[0].x = 2;
    game->snake.snake[0].y = 3;
    game->snake.snake[1].x = 2;
    game->snake.snake[1].y = 4;
    game->snake.snake[2].x = 2;
    game->snake.snake[2].y = 5;

    game->snake.taille = 3;
    game->snake.dir = BAS;
    game->snake.nextdir = BAS;

    game->levelMap[TAILLEX][TAILLEY];
    generation_fruit(game);

    for(x=0;x<TAILLEX;x++){
        for(y=0;y<TAILLEY;y++){
            if(x==0 || x==TAILLEX-1 || y==0 || y==TAILLEY-1)
                game->levelMap[x][y] = MUR;
            else
                game->levelMap[x][y] = VIDE;
        }
    }

    if(game->multiplayer==1){
    }

    //game->deplacement = SDL_AddTimer(300, deplacement_snake, &game);
}