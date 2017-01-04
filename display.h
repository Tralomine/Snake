#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

typedef struct{
    SDL_Surface *pic;
    SDL_Rect pos;
}Sprite;

typedef struct{
    SDL_Surface *pic;
    SDL_Rect pos, mask;             //plusieurs sprites sur la même image: on en prend juste 1
    int nbr_pics, current;
}LargeSprite;

void setSprite(Sprite* sprite, char* fileName);
void displaySprite(SDL_Surface* screen, Sprite* sprite, int x, int y);

void setLargeSprite(LargeSprite* sprite, char* fileName, int current);
void changeLargeSprite(LargeSprite* sprite, int current);
void displayLargeSprite(SDL_Surface* screen, LargeSprite* sprite, int x, int y);

void destroySprite(Sprite* sprite);
void destroyLargeSprite(LargeSprite* sprite);


#include "display.c"

#endif // DISPLAY_H_INCLUDED
