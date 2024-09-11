#include<SDL.h>
#include"Game.h"
#include"constants.h"


int main(int args, char* argc[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window{SDL_CreateWindow("Snake",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_WIDTH,0)};
    SDL_Renderer* renderer{SDL_CreateRenderer(window,-1,0)};

    Game game{renderer};

    game.play();

    return 0;
}
