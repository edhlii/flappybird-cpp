#include "game.h"

#include <iostream>

Game::Game() {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "bird");
  SetTargetFPS(60);
  SearchAndSetResourceDir("resources");
  loadTexture();
  bird.posX = 100;
  bird.posY = WINDOW_HEIGHT / 2;
}

Game::~Game() {
  UnloadTexture(backgroundTexture);
  UnloadTexture(birdTexture);
  UnloadTexture(pipeTexture);
  CloseWindow();
}

void Game::loadTexture() {
  Image backgroundImage = LoadImage("game-objects/background-day.png");
  ImageResize(&backgroundImage, WINDOW_WIDTH, WINDOW_HEIGHT);
  backgroundTexture = LoadTextureFromImage(backgroundImage);
  Image birdImage = LoadImage("game-objects/yellowbird-midflap.png");
  ImageResize(&birdImage, bird.WIDTH, bird.HEIGHT);
  birdTexture = LoadTextureFromImage(birdImage);
}

void Game::UpdateBirdPosition() {
  velocity += GRAVITY;
  bird.posY += velocity;
  return;
}

void Game::HandleInput() {
  if (IsKeyPressed(KEY_SPACE)) {
    velocity = -8;
  }
}

void Game::Run() {
  while (!WindowShouldClose()) {
    HandleInput();
    UpdateBirdPosition();
    BeginDrawing();

    delta = GetFrameTime();
    std::cout << delta << std::endl;
    ClearBackground(BLUE);
    DrawTexture(backgroundTexture, 0, 0, WHITE);
    DrawTexture(birdTexture, bird.posX, bird.posY, WHITE);
    // DrawRectangle(bird.posX, bird.posY, 10, 10, RED);

    EndDrawing();
  }
}