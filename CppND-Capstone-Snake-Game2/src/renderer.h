#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include <memory>

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  //Renderer(const Renderer &source);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food,SDL_Point const &specialFood);
  void Render(Snake const snake) ;
  void UpdateWindowTitle(int score, int fps);

 private:
 //NEW
  SDL_Window *sdl_window;
  //
  //std::shared_ptr<SDL_Window> sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif