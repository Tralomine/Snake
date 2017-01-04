#include <stdlib.h>
#include "../include/SDL/SDL.h"
#include "../include/SDL/SDL_image.h"

#include "button.h"

//creation du bouton
void setButton(Button* button, const char* file, int height, int width, int x, int y)
{
    button->surface = IMG_Load(file);
    button->pos.h = height;
    button->pos.w = width;
    button->pos.x = x;
    button->pos.y = y;
}

//affiche le bouton
void displayButton(Button button, SDL_Surface *screen)
{
    SDL_BlitSurface(button.surface, NULL, screen, &(button.pos));
}

//renvoie si le bouton a �t� click� ou pas
int buttonClicked(Button* button, SDL_Event* event)
{
    if(event->type==SDL_MOUSEBUTTONUP)
    {
        if((event->button.x > button->pos.x && event->button.x < button->pos.x + button->pos.w)&&   //on test si le click �tait bien sur le bouton
            (event->button.y > button->pos.y && event->button.y < button->pos.y + button->pos.h))
                return event->button.button; //on renvoie le click utilis�
    }
    return 0;
}

//le nom est pas assez explicit ?
void destroyButton(Button* button)
{
    SDL_FreeSurface(button->surface);
}
