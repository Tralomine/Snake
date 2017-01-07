#pragma once

#include "const.h"

typedef enum {VIDE, MUR, FRUIT, SNAKE} Map;
typedef enum {HAUT, BAS, DROITE, GAUCHE} Direction;

typedef struct{
    int x, y;
}Point;

typedef struct{
    Point corp[TAILLE_SNAKE_MAX];
    int taille, growWait;
    Direction dir, nextdir;
    int life;
    int collision; //stockage de la colision
}Snake;


void displaySnake(SDL_Surface* screen, Snake* snake, int numero);
void deplacement_snake(void* temp);
        //on est obligé de mettre un pointeur sur vide car on ne peux pas inclure game.h dans snake.h et snake.h dans game.h
