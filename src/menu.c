#include <stdlib.h>
#include "../include/SDL/SDL.h"
#include "../include/SDL/SDL_image.h"

#include "const.h"
#include "snake.h"
#include "button.h"
#include "game.h"

#include "menu.h"


void menu(Game* game)
{
    Button singlePlayer, multiPlayer;
    setButton(&singlePlayer, "texture/buttonSingle.png", 80, 200, 0, 100);

    SDL_Surface *background, *singlePlayerEater, *multiPlayerEater;
    SDL_Rect singleEaterPos, multiEaterPos;
    singlePlayerEater = IMG_Load("texture/singleEater.png");
    background = IMG_Load("texture/screen/background_menu.png");

    Bool done = FALSE;
    while(!done)
    {
        //event checking
        SDL_WaitEvent(&(game->event));
        if(buttonClicked(&singlePlayer, &(game->event))==SDL_BUTTON_LEFT)
        {
            setupGame(game);
            play(game);
        }

        switch (game->event.type)
        {
            // exit if the window is closed
            case SDL_QUIT:
                done = TRUE;
                break;

            // check for keypresses
            case SDL_KEYDOWN:
            {
                // quitte si on appuie sur ECHAP
                if (game->event.key.keysym.sym == SDLK_ESCAPE)
                    done = TRUE;
                break;
            }
        } // end switch

        //refreshing screen
        SDL_BlitSurface(background, NULL, game->screen, NULL);
        displayButton(singlePlayer, game->screen);
        SDL_BlitSurface( singlePlayerEater, NULL, game->screen, &singleEaterPos);
        SDL_Flip(game->screen);
    }


}

void levelMenu(Game *game)
{
    Button backMenu, levels[4], infinity;
}
