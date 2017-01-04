#ifndef SNAKEDISPLAY_H_INCLUDED
#define SNAKEDISPLAY_H_INCLUDED

typedef enum {VIDE, MUR, FRUIT} Map;
typedef enum {RIEN, HAUT, BAS, DROITE, GAUCHE} Direction;

typedef struct{
    int x, y;
}Point;

typedef struct{
    Point snake[TAILLE_SNAKE_MAX];
    int taille;
    Direction dir;
}Snake;

typedef struct{
    Snake snake;
    Map levelMap[TAILLEX][TAILLEY];
    int collision;
    Direction nextdir;
}Game;

void displaySnake(SDL_Surface *screen, Snake *snake);
Uint32 deplacement_snake(Uint32  intervalle, void* temp);

void displayMap(SDL_Surface* screen, Map levelMap[TAILLEX][TAILLEY]);

void generation_fruit(Game *game);


#include "snake.c"

#endif // SNAKEDISPLAY_H_INCLUDED
