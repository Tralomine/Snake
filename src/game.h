#pragma once

#include "../include/SDL/SDL_ttf.h"
#include "snake.h"

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
    TTF_Font* font;
    SDL_Color black;
}Game;


void displayMap(Game* game);

void play(Game* game);
void setupGame(Game* game);
void generation_fruit(Game* game);
