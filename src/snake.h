#ifndef SNAKEDISPLAY_H_INCLUDED
#define SNAKEDISPLAY_H_INCLUDED

typedef enum {VIDE, MUR, FRUIT, SNAKE} Map;
typedef enum {HAUT, BAS, DROITE, GAUCHE} Direction;

typedef struct{
    int x, y;
}Point;

typedef struct{
    Point snake[TAILLE_SNAKE_MAX];
    int taille;
    Direction dir, nextdir;
}Snake;


void displaySnake(SDL_Surface* screen, Snake* snake);
Uint32 deplacement_snake(Uint32  intervalle, void* temp);


#include "snake.c"

#endif // SNAKEDISPLAY_H_INCLUDED
