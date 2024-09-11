
#ifndef APPLE_H
#define APPLE_H

#include<SDL.h>
#include"Random/random.h"

class Apple{
public:
    SDL_Rect a;

    void generate(int screenWidth ,int side);

    void draw(SDL_Renderer* ren);
    
};
#endif
