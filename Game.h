#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include"constants.h"
#include"Snake.h"
#include<string>

class Score{
    TTF_Font* font{};
    std::string text{"Score: "};
public:
    Score(){
        TTF_Init();
        font=TTF_OpenFont("C:/Windows/Fonts/calibri.ttf",24);
    }
    void showScore(int score,SDL_Renderer* renderer){
        
        SDL_Surface* textSurface{TTF_RenderText_Solid(font,(text+std::to_string(score)).c_str(),{255,0,0})};

        SDL_Texture* texture{SDL_CreateTextureFromSurface(renderer,textSurface)};

        SDL_Rect rect{SCREEN_WIDTH/2,0,textSurface->w,textSurface->h};

        SDL_RenderCopy(renderer,texture,NULL,&rect);

        SDL_FreeSurface(textSurface);
    }
};


class Game{
    Snake snake;
    Apple apple{};
    Direction dir{};
    SDL_Renderer* renderer{};
    
public:
    Game(SDL_Renderer* ren):renderer{ren}{
        
        apple.generate(SCREEN_WIDTH,SIDE_LENGTH);

    }
    
    void play(){
        SDL_Texture* pauseScreen{IMG_LoadTexture(renderer,"images/pause.png")};
        SDL_Texture* gameOverScreen{IMG_LoadTexture(renderer,"images/gameover.png")};

        int applesEaten{0};
        Score scoreText;

        bool isPaused{false};
        bool isGameOver{false};

        SDL_Event e;
        while (true)
        {
            while (SDL_PollEvent(&e))
            {
                if(e.type==SDL_QUIT){

                    return;
                }
                
                else if(e.type==SDL_KEYDOWN){
                    switch (e.key.keysym.sym){
                    case SDLK_ESCAPE:
                        //pause the game
                        if(isGameOver) break;
                        
                        SDL_RenderCopy(renderer,pauseScreen,nullptr,nullptr);
                        SDL_RenderPresent(renderer);
                        isPaused=true;
                        break;                      
                    case SDLK_DOWN:
                        
                        if(dir!=UP && !(isPaused && isGameOver)) dir=DOWN;
                        break;
                    case SDLK_UP:
                        
                        if(dir!=DOWN && !(isPaused && isGameOver)) dir=UP;
                        break;
                    case SDLK_LEFT:
                        
                        if(dir!=RIGHT && !(isPaused && isGameOver)) dir=LEFT;
                        break;
                    case SDLK_RIGHT:
                        
                        if(dir!=LEFT && !(isPaused && isGameOver)) dir=RIGHT;
                        break;
                    case SDLK_r:
                        if(isPaused){
                            SDL_SetRenderDrawColor(renderer,0,0,0,255);
                            SDL_RenderClear(renderer);
                            isPaused=false;
                        }
                        break;
                    case SDLK_n:
                        if(isPaused || isGameOver){
                            snake.reset();
                            apple.generate(SCREEN_WIDTH,SIDE_LENGTH);

                            isPaused=false;
                            isGameOver=false;
                            applesEaten=0;
                        }
                        break;
                    case SDLK_q:
                        if(isPaused || isGameOver){
                            SDL_DestroyTexture(pauseScreen);
                            SDL_DestroyTexture(gameOverScreen);
                            return;
                        }
                    }

                }
            }

            if(isPaused || isGameOver){
                continue;
            } 

            if(snake.moveAndEatDetect(dir,apple)){
                apple.generate(SCREEN_WIDTH,SIDE_LENGTH);
                ++applesEaten;
            } 

            if(snake.bodyBoundaryCollision(SCREEN_WIDTH)){
                SDL_RenderCopy(renderer,gameOverScreen,nullptr,nullptr);
                
                SDL_RenderPresent(renderer);
                isGameOver=true;
                continue;

            } //show game over screen;

            //check for win: all apples gone

            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);

            
            snake.draw(renderer);
            apple.draw(renderer);
            scoreText.showScore(applesEaten,renderer);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
            
        }
    }
};
