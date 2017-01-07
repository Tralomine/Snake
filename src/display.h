#pragma once

typedef struct{
    SDL_Surface *pic;
    SDL_Rect pos;
}Sprite;

typedef struct{
    SDL_Surface *pic;
    SDL_Rect pos, mask;             //plusieurs sprites sur la meme image: on en prend juste 1
    int nbr_pics, current;
}LargeSprite;

void setSprite(Sprite* sprite, char* file);
void displaySprite(SDL_Surface* screen, Sprite* sprite, int x, int y);

LargeSprite setLargeSprite(char* file, int nbr_pics, int current);
void changeLargeSprite(LargeSprite* sprite, int current);
void displayLargeSprite(SDL_Surface* screen, LargeSprite* sprite, int x, int y);

void destroySprite(Sprite* sprite);
void destroyLargeSprite(LargeSprite* sprite);

Bool pauseDoubleButton(SDL_Surface* screen, char* backgroundFile, char* button1file, char* button2file);
void pauseButton(SDL_Surface* screen, char* backgroundFile, char* buttonFile);

