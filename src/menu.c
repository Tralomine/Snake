#include <stdlib.h>
#include "../include/SDL/SDL.h"
#include "../include/SDL/SDL_image.h"

#include "const.h"
#include "snake.h"
#include "button.h"
#include "game.h"
#include "display.h"

#include "menu.h"

///gere le choix entre les differents types de jeux/les credits/l'aide
Game menu(Game game)
{
    Button singlePlayer, multiPlayer, help, credits, quit;
    setButton(&singlePlayer, "texture/buttonSinglePlayer.png", 10, 250);
    setButton(&multiPlayer, "texture/buttonMultiPlayer.png", 10, 350);
    setButton(&help, "texture/buttonHelp.png", 10, 450);
    setButton(&credits, "texture/buttonCredits.png", 10, 550);
    setButton(&quit, "texture/buttonQuit.png", 10, 650);

    SDL_Surface* background = IMG_Load("texture/screen/background_menu.png");

    Bool done = FALSE; // done => Permet l'arret de la boucle infinie
    SDL_Event event;
    while(!done)
    {
        //afficher l'écran
        SDL_BlitSurface(background, NULL, game.screen, NULL);
        displayButton(singlePlayer, game.screen);
        displayButton(multiPlayer, game.screen);
        displayButton(credits, game.screen);
        displayButton(help, game.screen);
        displayButton(quit, game.screen);
        SDL_Flip(game.screen);

        SDL_WaitEvent(&event);

        //Gestion click
        if(buttonClicked(&quit, &event)==SDL_BUTTON_LEFT){
            eatButton(game.screen, quit.pos.y-26);
            done = TRUE;
        }
        switch (event.type){
            case SDL_QUIT:      //on quitte si on ferme la fenetre
                done = TRUE;
                break;
            case SDL_KEYDOWN:   //on quitte si on appuie sur ECHAP
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = TRUE;
                break;
        }
        if(buttonClicked(&singlePlayer, &event)==SDL_BUTTON_LEFT){
            eatButton(game.screen, singlePlayer.pos.y-26);
            game.multiplayer = FALSE;
            game = levelMenu(game);
        }
        if(buttonClicked(&multiPlayer, &event)==SDL_BUTTON_LEFT){
            eatButton(game.screen, multiPlayer.pos.y-26);
            game.multiplayer = TRUE;
            game = setupGameMulti(game);
            game = playMulti(game);
        }

        if(buttonClicked(&help, &event)==SDL_BUTTON_LEFT){
            eatButton(game.screen, help.pos.y-26);
            pauseButton(game.screen, "texture/screen/rules.png", "texture/back.png");
        }

        if(buttonClicked(&credits, &event)==SDL_BUTTON_LEFT){
            eatButton(game.screen, credits.pos.y-26);
            pauseButton(game.screen, "texture/screen/credits.png", "texture/back.png");
        }
    }

    //Liberation de la memoire
    destroyButton(&singlePlayer);
    destroyButton(&multiPlayer);
    destroyButton(&help);
    destroyButton(&credits);
    destroyButton(&quit);

    SDL_FreeSurface(background);


    return game;
}

///affiche le menu de choix entre les differents niveaux solo
Game levelMenu(Game game)
{
    pauseButton(game.screen, "texture/screen/load_sing.png", "texture/play.png");

    int x, y;
    SDL_Surface* background = IMG_Load("texture/screen/backgroundLevelMenu.png");

    Button backMenu, levels[4], infinity;
    for(x=0;x<2;x++){
        for(y=0;y<2;y++){
            char temp[32];
            sprintf(temp, "texture/lvl%i.png", x*2+y);
            setButton(&levels[x*2+y], temp, y*215+100, x*217+191);
        }
    }
    setButton(&backMenu, "texture/back.png", (LARGEUR-150)/2, HAUTEUR - 60);
    setButton(&infinity, "texture/levelInf.png", LARGEUR-492, 188);


    SDL_BlitSurface(background, NULL, game.screen, NULL);
    SDL_BlitSurface(backMenu.surface, NULL, game.screen, &backMenu.pos);
    for(x=0;x<4;x++){
        SDL_BlitSurface(levels[x].surface, NULL, game.screen, &levels[x].pos);}
    SDL_BlitSurface(infinity.surface, NULL, game.screen, &infinity.pos);

    SDL_Flip(game.screen);

    Bool done = FALSE, retourMenu = TRUE;  //si retourMenu == TRUE, on ne joue pas de level
    SDL_Event event;
    while(!done){
        SDL_WaitEvent(&event);
        if(buttonClicked(&backMenu, &event)==SDL_BUTTON_LEFT)
           done = TRUE;
        if(buttonClicked(&infinity, &event)==SDL_BUTTON_LEFT){
            done = TRUE;
            retourMenu = FALSE;
            game.level=-1;
        }
        for(x=0;x<4;x++){
            if(buttonClicked(&levels[x], &event)==SDL_BUTTON_LEFT){
                done = TRUE;
                retourMenu = FALSE;
                game.level=x;
            }
        }
        switch (event.type){
            case SDL_QUIT:  //Si click sur croix
                done = TRUE;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)   //Si click Echap
                    done = TRUE;
                break;
        }
    }

    destroyButton(&backMenu);
    for(x=0;x<4;x++){
        destroyButton(&levels[x]);}
    destroyButton(&infinity);

    if(!retourMenu)
        game = play(game);

    return game;
}

void eatButton(SDL_Surface* screen, int y)
{
    SDL_Surface* eater = IMG_Load("texture/eater.png");
    SDL_Surface* temp = SDL_CreateRGBSurface(0, LARGEUR, HAUTEUR, 32, 0, 0, 0, 0);
    SDL_Rect eaterPos;
    int x;

    SDL_BlitSurface(screen, NULL, temp, NULL);
    eaterPos.y = y;
    for(x=-768;x<-220;x+=2){
        SDL_BlitSurface(temp, NULL, screen, NULL);
        eaterPos.x = x;
        SDL_BlitSurface(eater, NULL, screen, &eaterPos);
        SDL_Flip(screen);
    }

    SDL_FreeSurface(eater);
    SDL_FreeSurface(temp);
}
