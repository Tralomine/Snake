#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "display.h"

void setSprite(Sprite* sprite, char* file)
{
    sprite->pic = IMG_Load(file);
}

void displaySprite(SDL_Surface* screen, Sprite* sprite, int x, int y)
{
    sprite->pos.x = x;
    sprite->pos.y = y;
    SDL_BlitSurface(sprite->pic, NULL, screen, &(sprite->pos));
}



void setLargeSprite(LargeSprite* sprite, char* file, int nbr_pics, int current)
{
    sprite->pic = IMG_Load(file);
    sprite->nbr_pics = nbr_pics;
    sprite->current = current;
    sprite->mask->x = sprite->pos.w / sprite->nbr_pics * sprite->current;
    sprite->mask->w = sprite->pos.w / sprite->nbr_pics;
    sprite->mask->h = sprite->pos.h;
}

void changeLargeSprite(LargeSprite* sprite, int current)
{
    sprite->current = current;
    sprite->mask->x = sprite->pos.w / sprite->nbr_pics * sprite->current;
}

void displayLargeSprite(SDL_Surface *screen, LargeSprite *sprite, int x, int y)
{
    sprite->pos.x = x;
    sprite->pos.y = y;
    SDL_BlitSurface(sprite->pic, sprite->mask, screen, &(sprite->pos));
}
