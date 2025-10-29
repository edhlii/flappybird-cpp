#include "renderer.h"

Texture Renderer::birdTexture;
Texture Renderer::pipeTexture;
Texture Renderer::backgroundTexture;

void Renderer::LoadTexture() {
  Image backgroundImage = LoadImage("game-objects/background-day.png");
  ImageResize(&backgroundImage, WINDOW_WIDTH, WINDOW_HEIGHT);
  backgroundTexture = LoadTextureFromImage(backgroundImage);
  std::cout << "Loaded background texture successfully" << std::endl;
  UnloadImage(backgroundImage);

  Image birdImage = LoadImage("game-objects/yellowbird-midflap.png");
  ImageResize(&birdImage, BIRD_WIDTH, BIRD_HEIGHT);
  birdTexture = LoadTextureFromImage(birdImage);
  std::cout << "Loaded bird texture succesfully" << std::endl;
  UnloadImage(birdImage);

  Image pipeImage = LoadImage("game-objects/pipe-green.png");
  ImageResize(&pipeImage, PIPE_WIDTH, PIPE_HEIGHT);
  pipeTexture = LoadTextureFromImage(pipeImage);
  UnloadImage(pipeImage);

  std::cout << "All resources loaded successfully" << std::endl;
}

void Renderer::RenderPipes(PipeManager& pipeManager) {
  std::vector<Pipe*> pipes = pipeManager.getPipeList();
  for (const auto& pipe : pipes) {
    // Draw pipe at the bottom
    Rectangle srcBottom = {0, 0, (float)PIPE_WIDTH, (float)PIPE_HEIGHT};
    Vector2 posBottom = {(float)pipe->getPosXBot(),
                         (float)(pipe->getPosYBot())};
    DrawTextureRec(pipeTexture, srcBottom, posBottom, WHITE);

    // Draw pipe at the top
    Rectangle srcTop = {0, 0, (float)PIPE_WIDTH, -(float)PIPE_HEIGHT};
    Vector2 posTop = {(float)pipe->getPosXTop(), (float)(pipe->getPosYTop())};
    DrawTextureRec(pipeTexture, srcTop, posTop, WHITE);
  }
}

void Renderer::RenderBird(Bird* bird) {
  DrawTexture(birdTexture, bird->getPosX(), bird->getPosY(), WHITE);
}

void Renderer::Render(Bird* bird, PipeManager& pipeManager, int currentState,
                      int score) {
  ClearBackground(BLUE);
  DrawTexture(backgroundTexture, 0, 0, WHITE);
  RenderBird(bird);
  RenderPipes(pipeManager);

  // Draw score
  std::string scoreText = "Score: " + std::to_string(score);
  DrawText(scoreText.c_str(), 0, 0, 40, RED);
  if (currentState == PAUSE) {
    DrawText("Press Enter to fly!", 100, 600, 40, BLUE);
  } else if (currentState == OVER) {
    DrawText("Game Over!", 100, 600, 75, RED);
    DrawText("Press Enter to try again!", 100, 700, 30, RED);
  }
}