#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "rivalSnake.h"
#include <memory>
class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height,int m);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  //~Game();
 private:
  Snake snake;

  SDL_Point food;
  SDL_Point specialFood;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  std::unique_ptr<RivalPlayer> r_player; 

  void PlaceFood();
  void Update();

  void SetRivalPlayer();

  void PlaceSpecialFood();
};

#endif