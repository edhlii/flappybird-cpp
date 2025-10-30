#pragma once
#include <string>
#include <vector>

// #include "agent.h"
#include "bird.h"
#include "common.h"
#include "pipe.h"
#include "pipeManager.h"
#include "raylib.h"
#include "renderer.h"
#include "resource_dir.h"

class Game {
 private:
  Texture birdTexture;
  Texture pipeTexture;
  Texture backgroundTexture;
  Bird* bird;
  PipeManager pipeManager;
  // Agent agent;
  double delta, timePassed = 0;
  int currentState;
  int score = 0;

 public:
  Game();
  ~Game();
  void Run();
  void Initialize();
  void HandleInput();
  void UpdateBirdPosition();
  bool IsCollide();
  void HandleCollision();
};