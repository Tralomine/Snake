#include <stdlib.h>
#include "../include/SDL/SDL.h"
#include "../include/SDL/SDL_image.h"
#include "../include/SDL/SDL_ttf.h"

#include "snake.h"
#include "display.h"
#include "button.h"
#include "game.h"

///joue le jeu solo
Game play(Game game)
{
    SDL_Surface *time, *score;

    char scoreTexte[255], timeTexte[255];
    SDL_Rect scorePos, timePos;
    scorePos.y = 0;
    timePos.y = 0;

    Uint32 interval1, interval2, seconde1, seconde2;

    game = setupGame(game);

    Bool done = FALSE, nextLevel, replay;

    Sprite life;
    setSprite(&life, "texture/life.png");

    int x;

    SDL_Event event;
    while (!done)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                done = TRUE;
                break;
            case SDL_KEYDOWN:
            {
                int touche = event.key.keysym.sym;

                if (touche == SDLK_ESCAPE)
                    done = TRUE;// quitte si on appuie sur ECHAP

                //si il peux tourner, il se prépare a tourner
                if(game.snake[0].dir == HAUT || game.snake[0].dir == BAS){
                    if(touche == SDLK_a) //'a' a la place de 'q' et 'w' a la place de 'z' parce que qwerty
                        game.snake[0].nextdir = GAUCHE;
                    if(touche == SDLK_d)
                        game.snake[0].nextdir = DROITE;
                }
                if(game.snake[0].dir == GAUCHE || game.snake[0].dir == DROITE){
                    if(touche == SDLK_w)
                        game.snake[0].nextdir = BAS;
                    if(touche == SDLK_s)
                        game.snake[0].nextdir = HAUT;
                }
                break;
            }
        }

        game = displayMap(game);
        displaySnake(game.screen, &(game.snake[0]), 1);


        sprintf(scoreTexte, "Score : %i", game.score);
        score = TTF_RenderText_Blended(game.font, scoreTexte, game.color);
        scorePos.x = (LARGEUR-score->w);
        SDL_BlitSurface(score, NULL, game.screen, &scorePos);

        if(game.time > -1){
            sprintf(timeTexte, "Temp restant : %i", game.time);
            time = TTF_RenderText_Blended(game.font, timeTexte, game.color);
            timePos.x = (LARGEUR-time->w)/2;
            SDL_BlitSurface(time, NULL, game.screen, &timePos);
        }

        if(game.snake[0].life>0)
            for(x=0;x<game.snake[0].life;x++){
                displaySprite(game.screen, &life, x*64, 0);
            }


        if(game.snake[0].collision == 1){
            game.snake[0].collision = 0;
            if(game.snake[0].life > 0)
                game.snake[0].life--;
            else
                done = TRUE;
        }

        if(game.time == 0){
            break;
        }

        game = eatFruit(game, 0);

        if(game.score > 20 && game.level > -1 && game.level < 4 ){
            nextLevel = pauseDoubleButton(game.screen, "texture/screen/win.png", "texture/back.png", "texture/next.png");
            game.win = TRUE;
            done = TRUE;
        }


        interval1 = SDL_GetTicks();
        if (interval1 - interval2 > game.speed){    //toutes les "vitesses" temps, on bouge le serpent
            deplacement_snake(&game);
            interval2 = interval1;
        }

        if(game.time > 0){
            seconde1 = SDL_GetTicks();
            if (seconde1 - seconde2 > 1000){      //toutes les secondes, on reduit le temps
                game.time--;
                seconde2 = seconde1;
            }
        }

        // Refresh l'écran
        SDL_Flip(game.screen);
    }

    if(game.win == FALSE)
        replay = pauseDoubleButton(game.screen, "texture/screen/gameOver.png", "texture/back.png", "texture/replay.png");

    if(replay == TRUE){
        replay = FALSE;
        game = setupGame(game);
        game = play(game);
    }

    if(game.win == TRUE && game.level < 3 && nextLevel == TRUE){
        game.level++;
        game = setupGame(game);
        game = play(game);
    }
    //si on est au dernier niveaux, on passe au niveau infini
    if(game.win == TRUE && game.level == 3 && nextLevel == TRUE){
        game.level = -1;
        game = setupGame(game);
        game = play(game);
    }

    return game;
}

///joue le jeu multi
Game playMulti(Game game)
{
    pauseButton(game.screen, "texture/screen/load_multi.png", "texture/play.png");

    Sprite life;
    setSprite(&life, "texture/life.png");

    int gagnant;
    int i;

    SDL_Event event;
    Bool done = FALSE;
    while (!done)
    {
        SDL_PollEvent(&event);
        switch (event.type){
            case SDL_QUIT:
                done = TRUE;
                break;
            case SDL_KEYDOWN:
            {
                int touche = event.key.keysym.sym;

                if (touche == SDLK_ESCAPE)
                    done = TRUE;

                //si il peux tourner, il se prépare a tourner
                if(game.snake[0].dir == HAUT || game.snake[0].dir == BAS){
                    if(touche == SDLK_a) //'a' a la place de 'q' et 'w' a la place de 'z' parce que qwerty
                        game.snake[0].nextdir = GAUCHE;
                    if(touche == SDLK_d)
                        game.snake[0].nextdir = DROITE;
                }
                if(game.snake[0].dir == GAUCHE || game.snake[0].dir == DROITE){
                    if(touche == SDLK_w)
                        game.snake[0].nextdir = BAS;
                    if(touche == SDLK_s)
                        game.snake[0].nextdir = HAUT;
                }
                //deuxiemme serpent
                if(game.snake[1].dir == HAUT || game.snake[1].dir == BAS){
                    if(touche == SDLK_k)
                        game.snake[1].nextdir = GAUCHE;
                    if(touche == SDLK_SEMICOLON) //qwerty et le m...
                        game.snake[1].nextdir = DROITE;
                }
                if(game.snake[1].dir == GAUCHE || game.snake[1].dir == DROITE){
                    if(touche == SDLK_o)
                        game.snake[1].nextdir = BAS;
                    if(touche == SDLK_l)
                        game.snake[1].nextdir = HAUT;
                }
                break;
            }
        }

        game = displayMap(game);
        displaySnake(game.screen, &game.snake[0], 1);
        displaySnake(game.screen, &game.snake[1], 2);

        //on affiche la vie de chaques joueurs de chaques cotés
        if(game.snake[0].life>0)
            for(i=0;i<game.snake[0].life;i++){
                displaySprite(game.screen, &life, i*64, 0);
            }
        if(game.snake[1].life>0)
            for(i=1;i<game.snake[0].life+1;i++){
                displaySprite(game.screen, &life, LARGEUR-i*64, 0);
            }


        for(i=0;i<2;i++){
            if(game.snake[i].collision == 1){
                if(game.snake[i].life > 0)
                    game.snake[i].life--;
                else
                    done = TRUE;
            }
            game = eatFruit(game, i);
        }

        Uint32 interval1, interval2;
        interval1 = SDL_GetTicks();
        if (interval1 - interval2 > game.speed){
            deplacement_snake(&game);
            interval2 = interval1;
        }

        // Refresh l'ecran
        SDL_Flip(game.screen);
    }

    if(game.snake[0].collision == 0 && game.snake[1].collision == 1)
        gagnant = 0;
    if(game.snake[0].collision == 1 && game.snake[1].collision == 0)
        gagnant = 1;
    if(game.snake[0].collision == 1 && game.snake[1].collision == 1)
        gagnant = -1;

    Bool replay;
    switch(gagnant)
    {
        case 0:
            replay = pauseDoubleButton(game.screen, "texture/screen/win1.png", "texture/back.png", "texture/replay.png");
            break;
        case 1:
            replay = pauseDoubleButton(game.screen, "texture/screen/win2.png", "texture/back.png", "texture/replay.png");
            break;
        default:
            replay = pauseDoubleButton(game.screen, "texture/screen/gameOver.png", "texture/back.png", "texture/replay.png");
    }

    if(replay == TRUE){
        game = setupGameMulti(game);
        game = playMulti(game);
    }

    return game;
}

///affiche les murs et les fruits en fonction de la carte
Game displayMap(Game game)
{
    Sprite wall, background;
    setSprite(&wall, "texture/brickWall.png");
    setSprite(&background, "texture/background.png");
    LargeSprite fruit = setLargeSprite("texture/fruit.png", 6, game.currentFruit);
    int x, y;

    for(x=0;x<TAILLEX;x++){
        for(y=0;y<TAILLEY;y++){
            displaySprite(game.screen, &background, x*TAILLESPRITE, y*TAILLESPRITE);
            if(game.levelMap[x][y]==MUR)
                displaySprite(game.screen, &wall, x*TAILLESPRITE, y*TAILLESPRITE);
            if(game.levelMap[x][y]==FRUIT)
                displayLargeSprite(game.screen, &fruit, x*TAILLESPRITE, y*TAILLESPRITE);
        }
    }
    destroySprite(&wall);
    destroySprite(&background);
    destroyLargeSprite(&fruit);

    return game;
}


///genere un nouveau fruit sur une case vide
Game generation_fruit(Game game)
{
    int fruit=0, fruit_x, fruit_y;
    int i, k, nbr_serpents = 1;

    if(game.multiplayer == TRUE)
        nbr_serpents = 2;

    while(fruit==0){
        fruit_x=rand()%TAILLEX;
        fruit_y=rand()%TAILLEY;
        if(game.levelMap[fruit_x][fruit_y] == VIDE){
            fruit=1;
        }

        //pas de fruit sur les serpent !
        for(k=0;k<nbr_serpents;k++){
            for(i=0;i<game.snake[k].taille;i++){
                if(game.snake[k].corp[i].x == fruit_x && game.snake[k].corp[i].y == fruit_y){
                    fruit = 0;
                    break;
                }
            }
        }

    }
    game.levelMap[fruit_x][fruit_y] = FRUIT;

    return game;
}

///initialize le jeu solo
Game setupGame(Game game)
{
    int x=0, y=0, dir;
    dir = rand()%4;
    switch(dir){
        case 0:
            x++;
            game.snake[0].dir = GAUCHE;
            game.snake[0].nextdir = GAUCHE;
            break;
        case 1:
            y++;
            game.snake[0].dir = BAS;
            game.snake[0].nextdir = BAS;
            break;
        case 2:
            x--;
            game.snake[0].dir = DROITE;
            game.snake[0].nextdir = DROITE;
            break;
        case 3:
            y--;
            game.snake[0].dir = HAUT;
            game.snake[0].nextdir = HAUT;
            break;
    }

    game.snake[0].corp[0].x = TAILLEX/2;
    game.snake[0].corp[0].y = TAILLEY/2;
    game.snake[0].corp[1].x = TAILLEX/2+x;
    game.snake[0].corp[1].y = TAILLEY/2+y;

    game.snake[0].taille = 2;
    game.snake[0].growWait = 2;

    game = loadLevel(game);  //on charge le niveau

    game.time = -1;

    if(game.level == 3)
        game.time = 100;

    game.currentFruit = rand()%6;

    game.score = 0;
    game.speed = 400;

    game.snake[0].life = 1;

    game.win = FALSE;

    return game;
}

///initialize le jeu en multi
Game setupGameMulti(Game game)
{
    int x=0, y=0, i;

    for(i=0;i<2;i++){
        x = 0;
        y = 0;
        int dir = rand()%4;
        switch(dir){
            case 0:
                x++;
                game.snake[i].dir = GAUCHE;
                game.snake[i].nextdir = GAUCHE;
                break;
            case 1:
                y++;
                game.snake[i].dir = BAS;
                game.snake[i].nextdir = BAS;
                break;
            case 2:
                x--;
                game.snake[i].dir = DROITE;
                game.snake[i].nextdir = DROITE;
                break;
            case 3:
                y--;
                game.snake[i].dir = HAUT;
                game.snake[i].nextdir = HAUT;
                break;
        }
        game.snake[i].corp[0].x = 5+4*i;
        game.snake[i].corp[0].y = 4+2*i;
        game.snake[i].corp[1].x = 5+4*i+x;
        game.snake[i].corp[1].y = 4+2*i+y;

        game.snake[i].taille = 1;
        game.snake[i].growWait = 2;

        game.snake[i].life = 1;
    }

    //on mets une map basique en multi
    for(x=0;x<TAILLEX;x++){
        for(y=0;y<TAILLEY;y++){
            if(x==0 || x==TAILLEX-1 || y==0 || y==TAILLEY-1)
                game.levelMap[x][y] = MUR;
            else
                game.levelMap[x][y] = VIDE;
        }
    }

    game.currentFruit = rand()%6;

    game.speed = 400;

    game = generation_fruit(game);

    return game;
}

///charge un niveau a partir d'un fichier, et le stock dans la carte
Game loadLevel(Game game)
{
    FILE* level;
    if(game.level == -1)
        level = fopen("levels/infinity.txt", "r");
    else{
        char temp[32];
        sprintf(temp, "levels/level%i.txt", game.level);
        level = fopen(temp, "r");
    }

    rewind(level);

    int x, y;
    for(x=0;x<TAILLEX;x++){
        for(y=0;y<TAILLEY;y++){
            char c;
            c = fgetc(level);
            switch(c){
                case '0':
                    game.levelMap[x][y] = VIDE;
                    break;
                case '1':
                    game.levelMap[x][y] = MUR;
                    break;
            }
        }
        fgetc(level); //on supprimme le \n a la fin de chaques lignes
    }

    game = generation_fruit(game);

    return game;
}

Game eatFruit(Game game, int i)
{
    if(game.snake[i].collision == 2){
        if(game.currentFruit==5){  //pasteque
            game.score+=2;
            game.snake[i].growWait+=3;
        }else if(game.currentFruit==0 && game.snake[i].taille>3){    //cerise
            game.snake[i].taille -= 2;
        }else{
            game.snake[i].growWait++;
        }
        if(game.currentFruit==3 && game.snake[i].life < 3)
            game.snake[i].life++;

        game.score++;
        game.snake[i].collision = 0;
        game.currentFruit = rand()%6;
        game = generation_fruit(game);
        game.speed = (int)(game.speed*0.95);
    }
    return game;
}
