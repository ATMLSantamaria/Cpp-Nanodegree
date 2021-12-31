#ifndef RIVALSNAKE_H
#define RIVALSNAKE_h
#include "snake.h"

class RivalSnake : public Snake {
    //speed = 0.2f;
};

class RivalPlayer {
 public:
  RivalPlayer(const Snake* snake, const SDL_Point* food,const SDL_Point* specialFood);
  ~RivalPlayer();
  void play();    // Play a single step of the game
 
 private:
  const Snake* snake;
  const SDL_Point* food;
  const SDL_Point* specialFood;
};

#endif