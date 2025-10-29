#include "game.h"

#include <iostream>

Game::Game() {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "bird");
  SetTargetFPS(60);
  SearchAndSetResourceDir("resources");
  Initialize();
}

void Game::Initialize() {
  pipeManager.reset();
  currentState = PAUSE;
  bird = new Bird();
  Renderer::LoadAllTexture();
  score = 0;
  std::cout << "Initialized successfully" << std::endl;
}

Game::~Game() {
  Renderer::UnloadAllTexture();
  delete bird;
  CloseWindow();
}

void Game::UpdateBirdPosition() { bird->updatePosition(); }

void Game::HandleInput() {
  // if (IsKeyPressed(KEY_ENTER)) {
  //   std::cout << "Enter" << std::endl;
  //   currentState = RUN;
  // }
  if (IsKeyPressed(KEY_SPACE) && currentState == RUN) {
    bird->setVelocity(-JUMP_FORCE); // Lực âm để bay lên
  }
  if (IsKeyPressed(KEY_ENTER)) {
    switch (currentState) {
    case PAUSE:
      currentState = RUN;
      break;
    case RUN:
      currentState = PAUSE;
      break;
    case OVER:
      currentState = PAUSE;
      Initialize();
      break;
    default:
      break;
    }
  }
}

// Check collision
bool Game::IsCollide() {
  // Ground, roof collide
  if (bird->getPosY() <= 0 ||
      bird->getPosY() + BIRD_HEIGHT >= WINDOW_HEIGHT - GROUND_HEIGHT)
    return 1;

  // Pipes collide
  std::vector<Pipe *> pipes = pipeManager.getPipeList();
  for (const auto &pipe : pipes) {
    Vector2 posBottom = {(float)pipe->getPosXBot(),
                         (float)(pipe->getPosYBot())};
    Vector2 posTop = {(float)pipe->getPosXTop(), (float)(pipe->getPosYTop())};

    // Check if posX collide
    if (bird->getPosX() + BIRD_WIDTH < posBottom.x ||
        bird->getPosX() > posBottom.x + PIPE_WIDTH) {
      continue;
    }

    // Update score
    if (bird->getPosX() >= posBottom.x + PIPE_WIDTH / 2) {
      if (!pipe->scoreIncreased) {
        pipe->scoreIncreased = 1;
        ++score;
      }
    }

    // Check if posY collide
    if (bird->getPosY() + BIRD_HEIGHT >= posBottom.y ||
        bird->getPosY() <= posTop.y + PIPE_HEIGHT) {
      // std::cout << "Collision detected" << std::endl;
      return 1;
    }
  }
  return 0;
}

void Game::HandleCollision() {
  bird->setDead(IsCollide());
  if (bird->isDead()) {
    currentState = OVER;
  }
}

void Game::Run() {
  while (!WindowShouldClose()) {
    // Manage game state

    if (currentState == RUN) {
      HandleInput();
      UpdateBirdPosition();
      pipeManager.updatePipeQueue();
      pipeManager.updatePipePosition();
      HandleCollision();
    } else {
      HandleInput();
    }

    BeginDrawing();
    Renderer::RenderPlayer(bird, pipeManager, currentState, score);
    EndDrawing();
  }
}