#include <stdlib.h>
#include "../include/SDL/SDL.h"
#include "../include/SDL/SDL_image.h"

#include "button.h"

///creation du bouton
void setButton(Button* button, const char* file, int x, int y)
{
    button->surface = NULL;
    button->surface = IMG_Load(file);
    if(!button->surface){
        fprintf(stderr, "impossible de charger l'image \"%s\" : %s", file, SDL_GetError);
        exit(EXIT_FAILURE);
    }
    button->pos.h = button->surface->h;
    button->pos.w = button->surface->w;
    button->pos.x = x;
    button->pos.y = y;
}

///affiche le bouton
void displayButton(Button button, SDL_Surface *screen)
{
    SDL_BlitSurface(button.surface, NULL, screen, &button.pos);
}

///renvoie si le bouton a été clické ou pas, et par quel click
int buttonClicked(Button* button, SDL_Event* event)
{
    if(event->type==SDL_MOUSEBUTTONUP)
    {
        if((event->button.x > button->pos.x && event->button.x < button->pos.x + button->pos.w)&&   //on test si le click était bien sur le bouton
            (event->button.y > button->pos.y && event->button.y < button->pos.y + button->pos.h))
                return event->button.button; //on renvoie le click utilisé
    }
    return 0;
}

//le nom est pas assez explicite ?
void destroyButton(Button* button)///Libere la memoire occupee par une structure
{
    SDL_FreeSurface(button->surface);
}
