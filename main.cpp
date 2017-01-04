#include <stdlib.h>

#include <SDL/SDL.h>

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

    // creation d'une fenetre
    SDL_Surface* screen = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen ){
        printf("Unable to set %ix%i video: %s\n", LARGEUR, HAUTEUR, SDL_GetError());
        return 1;}



    Game game;
    game.snake.snake[0].x = 2;
    game.snake.snake[0].y = 3;
    game.snake.snake[1].x = 2;
    game.snake.snake[1].y = 4;
    game.snake.snake[2].x = 3;
    game.snake.snake[2].y = 4;
    game.snake.taille = 6;
    game.snake.dir = DROITE;
    game.nextdir = DROITE;

    game.levelMap[TAILLEX][TAILLEY];
    int x, y;

    for(x=0;x<TAILLEX;x++){
        for(y=0;y<TAILLEY;y++){
            if(x==0 || x==TAILLEX-1 || y==0 || y==TAILLEY-1)
                game.levelMap[x][y] = MUR;
            else
                game.levelMap[x][y] = VIDE;
        }
    }

    generation_fruit(&game);

    SDL_TimerID timer;
    timer = SDL_AddTimer(333, deplacement_snake, &game);


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
                    if(event.key.keysym.sym == SDLK_a)
                        game.nextdir = GAUCHE;
                    if(event.key.keysym.sym == SDLK_d)
                        game.nextdir = DROITE;
                }
                if(game.snake.dir == GAUCHE || game.snake.dir == DROITE){
                    if(event.key.keysym.sym == SDLK_w)
                        game.nextdir = BAS;
                    if(event.key.keysym.sym == SDLK_s)
                        game.nextdir = HAUT;
                }
                break;
            }
        } // end switch

        // DEBUT DESSIN
        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        displayMap(screen, game.levelMap);
        displaySnake(screen, &(game.snake));

        if(game.collision == 1)
            break;

        if(game.collision == 2){
            generation_fruit(&game);
            game.collision = 0;
        }

//        if(SDL_GetTicks()>10000) //s'arrete au bout de x temps
//            break;

        // FIN DESSIN

        // Refresh l'écran
        SDL_Flip(screen);
    } // end main loop

    SDL_RemoveTimer(timer);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
