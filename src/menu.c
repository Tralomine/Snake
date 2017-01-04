#include <stdlib.h>
#include "../include/SDL/SDL.h"
#include "../include/SDL/SDL_image.h"

#include "const.h"
#include "snake.h"
#include "button.h"

#include "menu.h"


void menu(Game* game)
{
    Button singlePlayer, multiPlayer;
    setButton(&singlePlayer, "texture/buttonSingle.png", 80, 200, 0, 100);

    SDL_Surface *background, *singlePlayerEater, *multiPlayerEater;
    SDL_Rect singleEaterPos, multiEaterPos;
    singlePlayerEater = IMG_Load("texture/singleEater.png");

    int done=0;
    while(!done)
    {
        //event checking
        SDL_WaitEvent(&(game->event));
        if(buttonClicked(&singlePlayer, &(game->event))==SDL_BUTTON_LEFT)

        //refreshing screen
        SDL_BlitSurface( singlePlayerEater, NULL,game->screen, &singleEaterPos);
        displayButton(singlePlayer, game->screen);
    }


}

void levelMenu(Game *game)
{
    Button backMenu, levels[4], infinity;
}
