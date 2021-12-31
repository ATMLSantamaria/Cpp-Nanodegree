#include "game.h"
#include <iostream>
#include "SDL.h"
#include <chrono>
Game::Game(std::size_t grid_width, std::size_t grid_height,int m)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  if (m == 2) {
    SetRivalPlayer();
    //SetRivalPlayer(r_snake,food);
    }
  PlaceFood();
}

void Game::SetRivalPlayer() {
  r_player.reset(new RivalPlayer(&snake, &food,&specialFood));
}
void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  auto start = std::chrono::high_resolution_clock::now();
  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    if (r_player) {
      r_player->play();
      //renderer.Render(r_snake, food);
      }
    controller.HandleInput(running, snake);
    
    

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration<double,std::milli>(end-start).count();
    if (elapsed_time > 5000){
      //std::cout << "elapsed time = " << elapsed_time << "\n";
      PlaceSpecialFood();
      //food = specialFood;
      start = std::chrono::high_resolution_clock::now();
    }
    Update();
    renderer.Render(snake, food,specialFood);
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::PlaceSpecialFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      specialFood.x = x;
      specialFood.y = y;
      return;
    }
  }
}


void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
  if (specialFood.x == new_x && specialFood.y == new_y){
    score +=10;
    PlaceSpecialFood();
  }

}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
