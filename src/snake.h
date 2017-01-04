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

typedef struct{
    Snake snake;
    Map levelMap[TAILLEX][TAILLEY];
    int collision;
    int score;
    int currentFruit;
    int multiplayer, IA;
    SDL_Surface* screen;
    SDL_TimerID deplacement;
}Game;

void displaySnake(SDL_Surface *screen, Snake *snake);
Uint32 deplacement_snake(Uint32  intervalle, void* temp);

void displayMap(SDL_Surface* screen, Map levelMap[TAILLEX][TAILLEY]);

void setupGame(Game *game);
void generation_fruit(Game *game);


#include "snake.c"

#endif // SNAKEDISPLAY_H_INCLUDED
