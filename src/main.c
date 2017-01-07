#include <stdlib.h>

#include "../include/SDL/SDL.h"
#include "../include/SDL/SDL_image.h"

#include <time.h>

#include "const.h"
#include "snake.h"
#include "display.h"
#include "menu.h"
#include "game.h"


int main ( int argc, char** argv )
{
    srand(time(NULL)); //on initialize l'aleatoire aleatoirement

    // initialisation de la SDL
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 ){
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;}

    TTF_Init();

    //definition du nom de la fenetre
    SDL_WM_SetCaption("Snake", NULL);

    //definition d'un icone pour le snake
    SDL_Surface* icon = (SDL_Surface*)IMG_Load("texture/icon.ico");
    SDL_WM_SetIcon(icon, NULL);
    SDL_FreeSurface(icon);

    Game game;

    // creation d'une fenetre
    game.screen = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !game.screen ){
        printf("Unable to set %ix%i video: %s\n", LARGEUR, HAUTEUR, SDL_GetError());
        return 1;}

    //chargement de la police pour afficher le score
    game.font = TTF_OpenFont("texture/font/medium.otf",56);
    if(!game.font){
        fprintf(stderr, "error while loading font : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    game.color.r = 255;
    game.color.g = 255;
    game.color.b = 255;

    game = menu(game);

    TTF_CloseFont(game.font);

    return 0;
}
