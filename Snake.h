#ifndef SNAKE_H
#define SNAKE_H

#include<deque>
#include<SDL.h>
#include"Apple.h"
#include"Directions.h"
#include"constants.h"


struct Snake{


    SDL_Rect head;
    std::deque<SDL_Rect> body;
    int sideLen{};

public:
    Snake():head{SCREEN_WIDTH/2, SCREEN_WIDTH/2, SIDE_LENGTH, SIDE_LENGTH},sideLen{SIDE_LENGTH}{}

    bool appleCollision(Apple& apple);

    bool moveAndEatDetect(Direction dir,Apple& apple);

    bool bodyBoundaryCollision(int screenWidth);

    void draw(SDL_Renderer* ren);

    void reset(){
        head={SCREEN_WIDTH/2, SCREEN_WIDTH/2, SIDE_LENGTH, SIDE_LENGTH};
        body.clear();
    }
};

#endif
