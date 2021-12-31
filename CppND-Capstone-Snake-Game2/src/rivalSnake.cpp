#include <iostream>
#include "rivalSnake.h"
#include <math.h>
RivalPlayer::RivalPlayer(const Snake* snake, const SDL_Point* food,const SDL_Point* specialFood) : snake(snake), food(food),specialFood(specialFood){
    std::cout << "AutoSnake's Constructor called.\n";
};

RivalPlayer::~RivalPlayer() {
    std::cout << "AutoSnake's Destructor called.\n";
}

void RivalPlayer::play()
{
    // Find snake's head on the grid
    int cur_x = static_cast<int>(snake->head_x);
    int cur_y = static_cast<int>(snake->head_y);

    //Little Heuristic
    double distance_to_food = sqrt((double)(cur_x-food->x)*(double)(cur_x-food->x)+(double)(cur_y-food->y)*(double)(cur_y-food->y));
    double distance_to_SpecialFood = sqrt((double)(cur_x-specialFood->x)*(double)(cur_x-specialFood->x)+(double)(cur_y-specialFood->y)*(double)(cur_y-specialFood->y));
    if (distance_to_food < distance_to_SpecialFood){
        if (cur_x != food->x && cur_y != food->y) return;  
        if (cur_x == food->x && cur_y == food->y) return;      
    } else {
        if (cur_x != specialFood->x && cur_y != specialFood->y) return;  
        if (cur_x == specialFood->x && cur_y == specialFood->y) return;    
    }

    
    // Prepare an event
    SDL_Event sdlevent;
    sdlevent.type = SDL_KEYDOWN;
    // //Little heuric
    if (distance_to_food < distance_to_SpecialFood){
        //std::cout << "Distance to special fruit =" << distance_to_SpecialFood << "| Distance to food =" << distance_to_food << "\n";
        if (cur_x == food->x) 
        {
            if (cur_y > food->y) sdlevent.key.keysym.sym = SDLK_UP;
            else sdlevent.key.keysym.sym = SDLK_DOWN;
        }
        else // cur_y == food.y
        {
            if (cur_x > food->x) sdlevent.key.keysym.sym = SDLK_LEFT;
            else sdlevent.key.keysym.sym = SDLK_RIGHT;
        }        
    } else {
        if (cur_x == specialFood->x) 
        {
            if (cur_y > specialFood->y) sdlevent.key.keysym.sym = SDLK_UP;
            else sdlevent.key.keysym.sym = SDLK_DOWN;
        }
        else // cur_y == food.y
        {
            if (cur_x > specialFood->x) sdlevent.key.keysym.sym = SDLK_LEFT;
            else sdlevent.key.keysym.sym = SDLK_RIGHT;
        }  
    }


    SDL_PushEvent(&sdlevent);
}