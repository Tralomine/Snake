#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED


typedef struct{
    Snake snake, snake2;
    Map levelMap[TAILLEX][TAILLEY];
    int collision, collision2;
    int score;
    int currentFruit;
    int multiplayer, IA;
    SDL_Surface* screen;
    SDL_TimerID deplacement;
    SDL_Event event;
}Game;


void displayMap(Game* game);

void play(Game* game);
void setupGame(Game *game);
void generation_fruit(Game *game);

#include "game.c"

#endif // GAME_H_INCLUDED
