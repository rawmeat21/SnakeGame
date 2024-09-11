#include"Snake.h"

bool Snake::moveAndEatDetect(Direction dir,Apple& apple){
    bool ateApple{true};

    body.push_front({head.x,head.y,head.w,head.h});

    switch (dir)
    {
    case DOWN:
        head.y+=sideLen;
        break;
    case UP:
        head.y-=sideLen;
        break;
    case LEFT:
        head.x-=sideLen;
        break;
    case RIGHT:
        head.x+=sideLen;
        break;
    }

    if(!appleCollision(apple)){
    body.pop_back();
    ateApple=false;
    }
    return ateApple;
}

bool Snake::bodyBoundaryCollision(int screenWidth){

    for (auto i{body.begin()}; i !=body.end(); ++i)
    {
        if(i->x == head.x && i->y==head.y) return true;
    }

    if(head.x>=screenWidth || head.x<0 || head.y<0 || head.y>=screenWidth) return true;

    return false;
}

bool Snake::appleCollision(Apple& apple){
    return (head.x==apple.a.x && head.y==apple.a.y);
}

void Snake::draw(SDL_Renderer* ren){

    SDL_SetRenderDrawColor(ren, 255,255,255,255);
    SDL_RenderFillRect(ren,&head);

    for (int i{0}; i < body.size(); ++i){
        SDL_SetRenderDrawColor(ren, 255,255,255,255);
        SDL_RenderFillRect(ren,&body[i]);
    }
}
