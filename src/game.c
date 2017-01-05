#include <stdlib.h>
#include "../include/SDL/SDL.h"
#include "../include/SDL/SDL_image.h"

#include "snake.h"
#include "display.h"
#include "game.h"

void play(Game* game)
{
    int speed = 400;

    // program main loop
    Bool done = FALSE;
    while (!done)
    {
        // message processing loop
        SDL_PollEvent(&(game->event));
        // check for messages
        switch (game->event.type)
        {
            // exit if the window is closed
            case SDL_QUIT:
                done = TRUE;
                break;

            // check for keypresses
            case SDL_KEYDOWN:
            {
                int touche = game->event.key.keysym.sym;
                // quitte si on appuie sur ECHAP
                if (touche == SDLK_ESCAPE)
                    done = TRUE;

                //si il peux tourner, il se prépare a tourner
                if(game->snake.dir == HAUT || game->snake.dir == BAS){
                    if(touche == SDLK_a) //'a' a la place de 'q' et 'w' a la place de 'z' parce que qwerty
                        game->snake.nextdir = GAUCHE;
                    if(touche == SDLK_d)
                        game->snake.nextdir = DROITE;
                }
                if(game->snake.dir == GAUCHE || game->snake.dir == DROITE){
                    if(touche == SDLK_w)
                        game->snake.nextdir = BAS;
                    if(touche == SDLK_s)
                        game->snake.nextdir = HAUT;
                }
                break;
            }
        } // end switch

        // DEBUT DESSIN


        displayMap(game);
        displaySnake(game->screen, &(game->snake));

        char scoreTexte[255];
        sprintf(scoreTexte, "Score : %i", game->score);
        SDL_Surface* texte = TTF_RenderText_Blended(game->font, scoreTexte, game->black);
        SDL_Rect pos;
        pos.x = (LARGEUR-texte->w)/2;
        pos.y = HAUTEUR-64;
        SDL_BlitSurface(texte, NULL, game->screen, &pos);


        if(game->collision == 1){
            game->collision = 0;
            break;
        }

        if(game->collision == 2){
            if(game->currentFruit==5){  //pasteque
                game->score+=3;
                game->snake.growWait+=3;
            }else if(game->currentFruit==0 && game->snake.taille>3){    //cerise
                game->snake.taille -= 2;
            }else{
                game->snake.growWait++;
            }
            game->score++;
            game->collision = 0;
            game->currentFruit = rand()%6;
            generation_fruit(game);
            speed = (int)(speed*0.95);
        }


        Uint32 interval1, interval2;
        interval1 = SDL_GetTicks();
        if (interval1 - interval2 > speed)
        {
            deplacement_snake(interval1, game);    //le timer ne... marche pas ???
            interval2 = interval1;
        }


//        if(SDL_GetTicks()>10000) //s'arrete au bout de x temps
//            break;

        // FIN DESSIN

        // Refresh l'écran
        SDL_Flip(game->screen);
    } // end main loop
}



void displayMap(Game* game)
{
    Sprite wall, background;
    setSprite(&wall, "texture/brickWall.png");
    setSprite(&background, "texture/background.png");
    LargeSprite fruit;
    setLargeSprite(&fruit, "texture/fruit.png", 6, game->currentFruit);
    int x, y;

    for(x=0;x<TAILLEX;x++){
        for(y=0;y<TAILLEY;y++){
            displaySprite(game->screen, &background, x*TAILLESPRITE, y*TAILLESPRITE);
            if(game->levelMap[x][y]==MUR)
                displaySprite(game->screen, &wall, x*TAILLESPRITE, y*TAILLESPRITE);
            if(game->levelMap[x][y]==FRUIT)
                displayLargeSprite(game->screen, &fruit, x*TAILLESPRITE, y*TAILLESPRITE);
        }
    }
    destroySprite(&wall);
    destroySprite(&background);
    destroyLargeSprite(&fruit);
}


//genere un nouveau fruit sur une case vide
void generation_fruit(Game* game)
{
    int fruit=0, fruit_x, fruit_y;
    int i;
    while(fruit==0){
        fruit_x=rand()%TAILLEX;
        fruit_y=rand()%TAILLEY;
        if(game->levelMap[fruit_x][fruit_y] == VIDE){
            fruit=1;
        }
        for(i=0;i<game->snake.taille;i++){
            if(game->snake.snake[i].x == fruit_x && game->snake.snake[i].y == fruit_y){
                fruit = 0;
                break;
            }
        }
    }
    game->levelMap[fruit_x][fruit_y] = FRUIT;
}

void setupGame(Game* game)
{
    int x=0, y=0, dir;
    dir = rand()%4;
    switch(dir){
        case 0:
            x++;
            game->snake.dir = GAUCHE;
            game->snake.nextdir = GAUCHE;
            break;
        case 1:
            y++;
            game->snake.dir = BAS;
            game->snake.nextdir = BAS;
            break;
        case 2:
            x--;
            game->snake.dir = DROITE;
            game->snake.nextdir = DROITE;
            break;
        case 3:
            y--;
            game->snake.dir = HAUT;
            game->snake.nextdir = HAUT;
            break;
    }


    game->snake.snake[0].x = TAILLEX/2;
    game->snake.snake[0].y = TAILLEY/2;
    game->snake.snake[1].x = TAILLEX/2+x;
    game->snake.snake[1].y = TAILLEY/2+y;

    game->snake.taille = 2;
    game->snake.growWait = 2;

    game->levelMap[TAILLEX][TAILLEY];

    game->currentFruit = rand()%6;

    for(x=0;x<TAILLEX;x++){
        for(y=0;y<TAILLEY;y++){
            if(x==0 || x==TAILLEX-1 || y==0 || y==TAILLEY-1)
                game->levelMap[x][y] = MUR;
            else
                game->levelMap[x][y] = VIDE;
        }
    }

    game->black.r = 0;
    game->black.g = 0;
    game->black.b = 0;
    game->font = TTF_OpenFont("texture/font/FiraSans-Medium.otf",56);

    game->score = 0;

    generation_fruit(game);

    if(game->multiplayer==1){
    }

    //game->deplacement = SDL_AddTimer(300, deplacement_snake, &game);
}
