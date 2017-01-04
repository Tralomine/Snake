#include <stdlib.h>

#include <SDL/SDL.h>

#include "const.h"
#include "snake.h"
#include "display.h"


int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;}

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen ){
        printf("Unable to set %ix%i video: %s\n", LARGEUR, HAUTEUR, SDL_GetError());
        return 1;}



    Snake snake;
    snake.snake[0].x = 2;
    snake.snake[0].y = 3;
    snake.snake[1].x = 2;
    snake.snake[1].y = 4;
    snake.snake[2].x = 3;
    snake.snake[2].y = 4;
    snake.snake[3].x = 4;
    snake.snake[3].y = 4;
    snake.snake[4].x = 5;
    snake.snake[4].y = 4;
    snake.snake[5].x = 5;
    snake.snake[5].y = 3;
    snake.taille = 6;


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
                // exit if ESCAPE is pressed
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
                break;
            }
        } // end switch

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // DRAWING ENDS HERE
        displaySnake(screen, &snake);

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
