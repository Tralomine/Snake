#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "display.h"
#include "snake.h"

void displaySnake(SDL_Surface* screen, Snake *snake)
{
    LargeSprite snakeHead, snakeTail, snakeBody;
    setLargeSprite(&snakeHead, "texture/snake_head.png", 4, 0);
    setLargeSprite(&snakeBody, "texture/snake_body.png", 5, 0);

    displayLargeSprite(screen, &snakeHead, snake->snake[0].x*TAILLECASE, snake->snake[0].y*TAILLECASE);

    int i;
    for(i=1;i<snake->taille-1;i++){
        displayLargeSprite(screen, &snakeBody, snake->snake[i].x*TAILLECASE, snake->snake[i].y*TAILLECASE);
    }
}
