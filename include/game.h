#pragma once
#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <vector>

#include "agent.h"
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
  Bird *bird;
  PipeManager pipeManager;
  Agent *agent0;
  std::vector<Agent *> agents;
  float groundX1 = 0, groundX2 = 0;
  double delta, timePassed = 0;
  int currentState;
  int aiType = -1;
  int score = 0;

public:
  Game();
  ~Game();

  void UpdateGround();

  void RunPlayer();
  void RunAgent0();
  void RunAgent1();
  void Run();
  void Initialize();
  void HandleInput();
  bool IsCollide(Bird *bird);
  void HandleCollision(Bird *bird);
  void NewGeneration();
};