#include <stdlib.h>

#include "../include/SDL/SDL.h"

#include "time.h"

#include "const.h"
#include "snake.h"
#include "display.h"


int main ( int argc, char** argv )
{
    srand(time(NULL)); //on initialize l'aléatoire aléatoirement

    // initialisation de la SDL
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 ){
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;}


    Game game;

    // creation d'une fenetre
    game.screen = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !game.screen ){
        printf("Unable to set %ix%i video: %s\n", LARGEUR, HAUTEUR, SDL_GetError());
        return 1;}

    setupGame(&game);

    SDL_Event event;
    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_PollEvent(&event);
        // check for messages
        switch (event.type)
        {
            // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

            // check for keypresses
            case SDL_KEYDOWN:
            {
                // quitte si on appuie sur ECHAP
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = true;

                //si il peux tourner, il se prépare a tourner
                if(game.snake.dir == HAUT || game.snake.dir == BAS){
                    if(event.key.keysym.sym == SDLK_a) //'a' a la place de 'q' et 'w' a la place de 'z' parce que qwerty
                        game.snake.nextdir = GAUCHE;
                    if(event.key.keysym.sym == SDLK_d)
                        game.snake.nextdir = DROITE;
                }
                if(game.snake.dir == GAUCHE || game.snake.dir == DROITE){
                    if(event.key.keysym.sym == SDLK_w)
                        game.snake.nextdir = BAS;
                    if(event.key.keysym.sym == SDLK_s)
                        game.snake.nextdir = HAUT;
                }
                break;
            }
        } // end switch

        // DEBUT DESSIN

        displayMap(game.screen, game.levelMap);
        displaySnake(game.screen, &(game.snake));


        if(game.collision == 1){
            game.collision = 0;
            break;
        }

        if(game.collision == 2){
            game.collision = 0;
            generation_fruit(&game);
        }

//        if(SDL_GetTicks()>10000) //s'arrete au bout de x temps
//            break;

        // FIN DESSIN

        // Refresh l'écran
        SDL_Flip(game.screen);
    } // end main loop

    SDL_RemoveTimer(game.deplacement);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
