#pragma once
#include "bird.h"
#include "common.h"
#include "pipe.h"
#include "raylib.h"
#include "resource_dir.h"
#include <string>
#include <vector>

class Game {
public:
  const int WINDOW_HEIGHT = 800;
  const int WINDOW_WIDTH = 600;
  const double GRAVITY = 0.2;
  const double ACCEL = 8;
  Game();
  ~Game();
  void Run();
  Texture birdTexture;
  Texture pipeTexture;
  Texture backgroundTexture;
  Bird *bird;
  std::vector<Pipe *> pipes;
  double delta, timePassed = 0;
  int currentState;
  int score = 0;

private:
  void LoadTexture();
  void Initialize();
  void HandleInput();
  void UpdateBirdPosition();
  void UpdatePipeQueue();
  bool IsCollide();
  void HandleCollision();
  void Render();
};