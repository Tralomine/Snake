#include <stdlib.h>
#include "../include/SDL/SDL.h"
#include "../include/SDL/SDL_image.h"
#include "../include/SDL/SDL_ttf.h"

#include "const.h"
#include "display.h"
#include "button.h"

void setSprite(Sprite* sprite, char* file)
{
    sprite->pic = NULL;
    sprite->pic = IMG_Load(file);
    if(!sprite->pic){
        fprintf(stderr, "impossible de charger l'image \"%s\" : %s", file, SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void displaySprite(SDL_Surface* screen, Sprite* sprite, int x, int y)
{
    sprite->pos.x = x;
    sprite->pos.y = y;
    SDL_BlitSurface(sprite->pic, NULL, screen, &(sprite->pos));
}

void destroySprite(Sprite* sprite)
{
    SDL_FreeSurface(sprite->pic);
}



LargeSprite setLargeSprite(char* file, int nbr_pics, int current)
{
    LargeSprite sprite;

    sprite.pic = NULL;
    sprite.pic = IMG_Load(file);
    if(!sprite.pic){
        fprintf(stderr, "impossible de charger l'image \"%s\" : %s", file, SDL_GetError());
        exit(EXIT_FAILURE);
    }
    sprite.nbr_pics = nbr_pics;
    sprite.current = current;
    sprite.mask.w = TAILLESPRITE;
    sprite.mask.x = TAILLESPRITE * sprite.current;
    sprite.mask.y = 0;
    sprite.mask.h = TAILLESPRITE;

    return sprite;
}

void changeLargeSprite(LargeSprite* sprite, int current)
{
    sprite->current = current;
    sprite->mask.x = TAILLESPRITE * sprite->current;
}

void displayLargeSprite(SDL_Surface *screen, LargeSprite *sprite, int x, int y)
{
    sprite->pos.x = x;
    sprite->pos.y = y;
    SDL_BlitSurface(sprite->pic, &(sprite->mask), screen, &(sprite->pos));
}

void destroyLargeSprite(LargeSprite* sprite)
{
    SDL_FreeSurface(sprite->pic);
}


Bool pauseDoubleButton(SDL_Surface* screen, char* backgroundFile, char* button1file, char* button2file)
{
    SDL_Surface* background = IMG_Load(backgroundFile);
    Button button1, button2;
    setButton(&button1, button1file, (LARGEUR-150)/2-80, HAUTEUR - 60);
    setButton(&button2, button2file, (LARGEUR-150)/2+80, HAUTEUR - 60);

    SDL_BlitSurface(background, NULL, screen, NULL);
    displayButton(button1, screen);
    displayButton(button2, screen);
    SDL_Flip(screen);

    SDL_Event event;
    Bool done = FALSE;
    while(!done){
        SDL_WaitEvent(&event);
        if(buttonClicked(&button2, &event)==SDL_BUTTON_LEFT){

            destroyButton(&button1);
            destroyButton(&button2);
            SDL_FreeSurface(background);

            return TRUE;
        }
        if(buttonClicked(&button1, &event)==SDL_BUTTON_LEFT){

            destroyButton(&button1);
            destroyButton(&button2);
            SDL_FreeSurface(background);

            return FALSE;
        }
        switch (event.type){
            case SDL_QUIT:
                done = TRUE;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = TRUE;
                break;
        }
    }
    destroyButton(&button1);
    destroyButton(&button2);
    SDL_FreeSurface(background);

    return FALSE;
}


void pauseButton(SDL_Surface* screen, char* backgroundFile, char* buttonFile)
{
    SDL_Surface* background = IMG_Load(backgroundFile);
    Button button;
    setButton(&button, buttonFile, (LARGEUR-150)/2, HAUTEUR - 60);

    SDL_BlitSurface(background, NULL, screen, NULL);
    displayButton(button, screen);
    SDL_Flip(screen);

    SDL_Event event;
    Bool done = FALSE;
    while(!done){
        SDL_WaitEvent(&event);
        if(buttonClicked(&button, &event)==SDL_BUTTON_LEFT)
           done = TRUE;
        switch (event.type){
            case SDL_QUIT:
                done = TRUE;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = TRUE;
                break;
        }
    }
    destroyButton(&button);
    SDL_FreeSurface(background);
}
