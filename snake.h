#ifndef SNAKEDISPLAY_H_INCLUDED
#define SNAKEDISPLAY_H_INCLUDED


typedef enum {HAUT, BAS, DROITE, GAUCHE, VOID} Direction;

typedef struct{
    int x, y;
}Point;

typedef struct{
    Point snake[TAILLE_SNAKE_MAX];
    int taille;
    Direction dir;
}Snake;

void displaySnake(SDL_Surface *screen, Snake *snake);


#include "snake.c"

#endif // SNAKEDISPLAY_H_INCLUDED
