#include "game.h"

#include <iostream>

Game::Game() {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "bird");
  SetTargetFPS(60);
  SearchAndSetResourceDir("resources");
  currentState = RUN;
  bird = new Bird();
  pipes.push_back(new Pipe());

  loadTexture();
  bird->posX = 100;
  bird->posY = WINDOW_HEIGHT / 2;
  std::cout << "Initialized successfully" << std::endl;
}

Game::~Game() {
  UnloadTexture(backgroundTexture);
  UnloadTexture(birdTexture);
  UnloadTexture(pipeTexture);
  delete bird;
  CloseWindow();
}

void Game::loadTexture() {
  Image backgroundImage = LoadImage("game-objects/background-day.png");
  ImageResize(&backgroundImage, WINDOW_WIDTH, WINDOW_HEIGHT);
  backgroundTexture = LoadTextureFromImage(backgroundImage);
  std::cout << "Loaded background texture successfully" << std::endl;

  Image birdImage = LoadImage("game-objects/yellowbird-midflap.png");
  ImageResize(&birdImage, bird->WIDTH, bird->HEIGHT);
  birdTexture = LoadTextureFromImage(birdImage);
  std::cout << "Loaded bird texture succesfully" << std::endl;
  Image pipeImage = LoadImage("game-objects/pipe-green.png");
  ImageResize(&pipeImage, PIPE_WIDTH, PIPE_HEIGHT);
  pipeTexture = LoadTextureFromImage(pipeImage);
}

void Game::UpdateBirdPosition() {
  bird->velocity += GRAVITY;
  bird->posY += bird->velocity;
  return;
}

// Add pipe to the pipes queue
void Game::UpdatePipeQueue() {
  if (pipes.back()->posX <= WINDOW_WIDTH - 200) {
    pipes.push_back(new Pipe());
  }
  while (pipes.back()->posX < -20) {
    pipes.pop_back();
  }
  for (auto &pipe : pipes) {
    pipe->posX -= PIPE_VELOCITY;
  }
}

void Game::HandleInput() {
  if (IsKeyPressed(KEY_SPACE)) {
    bird->velocity = -8;
  }
}

// Check collision
bool Game::IsCollide() {
  for (const auto &pipe : pipes) {
    Vector2 posBottom = {(float)pipe->posX, (float)(pipe->posY)};
    Vector2 posTop = {(float)pipe->posX, (float)(-pipe->spaceWidth)};
    if (bird->posX + bird->WIDTH < posBottom.x ||
        bird->posX + bird->WIDTH > posBottom.x + PIPE_WIDTH)
      continue;
    if (bird->posY + bird->HEIGHT >= posBottom.y ||
        bird->posY <= posTop.y + PIPE_HEIGHT) {
      std::cout << "Collision detected" << std::endl;
      return 1;
    }
  }
  return 0;
}

void Game::HandleCollision() {
  if (IsCollide()) {
    currentState = OVER;
  }
}

void Game::Run() {
  while (!WindowShouldClose()) {
    if (currentState == RUN) {
      HandleInput();
      UpdateBirdPosition();
      UpdatePipeQueue();
      HandleCollision();
    }
    BeginDrawing();

    // delta = GetFrameTime();
    // std::cout << delta << std::endl;
    ClearBackground(BLUE);
    DrawTexture(backgroundTexture, 0, 0, WHITE);
    DrawTexture(birdTexture, bird->posX, bird->posY, WHITE);

    for (const auto &pipe : pipes) {
      Rectangle srcBottom = {0, 0, (float)PIPE_WIDTH, (float)PIPE_HEIGHT};
      Vector2 posBottom = {(float)pipe->posX, (float)(pipe->posY)};
      // Vector2 posBottom = {(float)pipe->posX, (float)(pipe->posY)};
      DrawTextureRec(pipeTexture, srcBottom, posBottom, WHITE);

      Rectangle srcTop = {0, 0, (float)PIPE_WIDTH, -(float)PIPE_HEIGHT};
      Vector2 posTop = {(float)pipe->posX, (float)(-pipe->spaceWidth)};
      DrawTextureRec(pipeTexture, srcTop, posTop, WHITE);
    }
    // DrawRectangle(bird.posX, bird.posY, 10, 10, RED);

    EndDrawing();
  }
}