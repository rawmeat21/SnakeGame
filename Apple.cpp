#include"Apple.H"

void Apple::generate(int screenWidth ,int side){
    int x{Random::get(0,screenWidth/side-1)*side};
    int y{Random::get(1,screenWidth/side-1)*side};

    a=SDL_Rect{x,y,side,side};
}

void Apple::draw(SDL_Renderer* ren){
    SDL_SetRenderDrawColor(ren, 255,0,0,255);
    SDL_RenderFillRect(ren,&a);
}
