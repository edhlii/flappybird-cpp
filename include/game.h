#pragma once
#include "bird.h"
#include "raylib.h"
#include "resource_dir.h"

class Game {
 public:
  const int WINDOW_HEIGHT = 800;
  const int WINDOW_WIDTH = 600;
  const double GRAVITY = 0.2;
  const double ACCEL = 8;
  Game();
  ~Game();
  void Run();
  void loadTexture();
  Texture birdTexture;
  Texture pipeTexture;
  Texture backgroundTexture;
  Bird bird;
  double delta, timePassed = 0;
  double velocity = 0;

 private:
  void HandleInput();
  void UpdateBirdPosition();
};