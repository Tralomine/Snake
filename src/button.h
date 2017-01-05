#pragma once

typedef struct Button Button;
struct Button
{
    SDL_Rect pos;
    SDL_Surface *surface;
};

enum buttonEvent
{LEFTCLICK,RIGHTCLICK,NOCLICK};

void setButton(Button* button, const char* file, int height, int width, int x, int y);
void displayButton(Button button, SDL_Surface *screen);
int buttonClicked(Button* button, SDL_Event* event);
void destroyButton(Button* button);
