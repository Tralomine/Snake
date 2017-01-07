#pragma once

#include "../include/SDL/SDL_ttf.h"
#include "snake.h"

///structure contenant toutes les variables du jeu
typedef struct{
    Snake snake[2];    //serpent et serpent multijoueur
    Map levelMap[TAILLEX][TAILLEY];     //briques et fruits
    int score, level, time;       //score, numéro du niveaux en cour et temps restant
    int currentFruit, speed;    //type du fruit affiché et vitesse du serpent
    Bool multiplayer;       //mode de jeu
    SDL_Surface* screen;    //endroit ou on affiche le jeu
    TTF_Font* font;         //police d'écriture pour le score
    SDL_Color color;        //couleur d'affichage du score
    Bool win;
}Game;


Game displayMap(Game game);

Game play(Game game);
Game playMulti(Game game);
Game setupGame(Game game);
Game setupGameMulti(Game game);
Game generation_fruit(Game game);
Game loadLevel(Game game);

Game eatFruit(Game game, int i);
