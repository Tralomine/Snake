#include <stdlib.h>

#include "../include/SDL/SDL.h"

#include "time.h"

#include "const.h"
#include "snake.h"
#include "display.h"
#include "menu.h"
#include "game.h"


int main ( int argc, char** argv )
{
    srand(time(NULL)); //on initialize l'aléatoire aléatoirement

    // initialisation de la SDL
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 ){
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;}

    TTF_Init();

    Game game;

    // creation d'une fenetre
    game.screen = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !game.screen ){
        printf("Unable to set %ix%i video: %s\n", LARGEUR, HAUTEUR, SDL_GetError());
        return 1;}

    // program main loop
    Bool done = FALSE;
    while (!done)
    {
        // message processing loop
        SDL_PollEvent(&(game.event));
        // check for messages
        switch (game.event.type)
        {
            // exit if the window is closed
            case SDL_QUIT:
                done = TRUE;
                break;

            // check for keypresses
            case SDL_KEYDOWN:
            {
                // quitte si on appuie sur ECHAP
                if (game.event.key.keysym.sym == SDLK_ESCAPE)
                    done = TRUE;
                break;
            }
        } // end switch


        menu(&game);
        //SDL_Delay(1500); //j'arette juste pour qu'on puisse voir notre score x)


    } // end main loop


    TTF_CloseFont(game.font);

    SDL_RemoveTimer(game.deplacement);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
