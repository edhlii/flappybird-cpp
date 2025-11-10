#include "renderer.h"

Texture Renderer::birdTexture;
Texture Renderer::pipeTexture;
Texture Renderer::backgroundTexture;
Texture Renderer::groundTexture;

void Renderer::UnloadAllTexture() {
  UnloadTexture(backgroundTexture);
  UnloadTexture(birdTexture);
  UnloadTexture(pipeTexture);
}

void Renderer::LoadAllTexture() {
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

  Image groundImage = LoadImage("game-objects/base.png");
  ImageResize(&groundImage, GROUND_WIDTH, GROUND_HEIGHT);
  groundTexture = LoadTextureFromImage(groundImage);
  UnloadImage(groundImage);

  std::cout << "All resources loaded successfully" << std::endl;
}

void Renderer::RenderPipes(PipeManager &pipeManager) {
  std::vector<Pipe *> pipes = pipeManager.getPipeList();
  for (const auto &pipe : pipes) {
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

void Renderer::RenderGround(float groundX) {
  DrawTexture(groundTexture, groundX, WINDOW_HEIGHT - GROUND_HEIGHT, WHITE);
}

void Renderer::RenderBird(Bird *bird) {
  DrawTexture(birdTexture, bird->getPosX(), bird->getPosY(), WHITE);
}

void Renderer::RenderPlayer(Bird *bird, PipeManager &pipeManager,
                            int currentState, int score, int maxScore,
                            float groundX1, float groundX2) {
  ClearBackground(BLUE);
  DrawTexture(backgroundTexture, 0, 0, WHITE);
  RenderBird(bird);
  RenderPipes(pipeManager);
  RenderGround(groundX1);
  RenderGround(groundX2);

  // Draw score
  std::string scoreText = "Score: " + std::to_string(score);
  DrawText(scoreText.c_str(), 0, 0, 40, RED);
  // Draw max score
  std::string maxScoreText = "Best Score: " + std::to_string(maxScore);
  DrawText(maxScoreText.c_str(), 0, 50, 40, RED);

  if (currentState == PAUSE) {
    DrawText("Press Enter to fly!", 100, 600, 40, BLUE);
  } else if (currentState == OVER) {
    DrawText("Game Over!", 100, 600, 75, RED);
    DrawText("Press Enter to try again!", 100, 700, 30, RED);
  } else if (currentState == MENU) {
    RenderMenu();
  }

  double diff = 0;
  std::vector<Pipe *> pipes = pipeManager.getPipeList();
}

void Renderer::RenderAgent0(Agent *agent, PipeManager &pipeManager,
                            int currentState, int score, int maxScore,
                            float groundX1, float groundX2) {
  Bird *bird = agent->bird;
  ClearBackground(BLUE);
  DrawTexture(backgroundTexture, 0, 0, WHITE);
  RenderBird(bird);
  RenderPipes(pipeManager);
  RenderGround(groundX1);
  RenderGround(groundX2);

  // Draw score
  std::string scoreText = "Score: " + std::to_string(score);
  DrawText(scoreText.c_str(), 0, 0, 40, RED);
  // Draw max score
  std::string maxScoreText = "Best Score: " + std::to_string(maxScore);
  DrawText(maxScoreText.c_str(), 0, 50, 40, RED);

  if (currentState == PAUSE) {
    DrawText("Press Enter to fly!", 100, 600, 40, BLUE);
  } else if (currentState == OVER) {
    DrawText("Game Over!", 100, 600, 75, RED);
    DrawText("Press Enter to try again!", 100, 700, 30, RED);
  } else if (currentState == MENU) {
    RenderMenu();
  }

  double diff = 0;
  std::vector<Pipe *> pipes = pipeManager.getPipeList();
  for (Pipe *pipe : pipes) {
    // I made the width of the pipes twice the size of the bird.
    if (bird->getPosX() < pipe->getPosXBot() + PIPE_WIDTH * 0.65) {
      diff = (pipe->getPosYBot() + pipe->getPosYTop() + PIPE_HEIGHT) / 2;
      break;
    }
  }

  Color red = {255, 0, 0, 100};
  DrawLine(bird->getPosX(), bird->getPosY(), bird->getPosX(), diff, red);
}

void Renderer::RenderAgent1(std::vector<Agent *> agents,
                            PipeManager &pipeManager, int currentState,
                            int score, int maxScore, float groundX1,
                            float groundX2) {
  ClearBackground(BLUE);
  DrawTexture(backgroundTexture, 0, 0, WHITE);

  for (Agent *agent : agents) {
    if (agent->bird->isDead())
      continue;
    RenderBird(agent->bird);
  }

  RenderPipes(pipeManager);
  RenderGround(groundX1);
  RenderGround(groundX2);

  // Draw score
  std::string scoreText = "Score: " + std::to_string(score);
  DrawText(scoreText.c_str(), 0, 0, 40, RED);
  // Draw max score
  std::string maxScoreText = "Best Score: " + std::to_string(maxScore);
  DrawText(maxScoreText.c_str(), 0, 50, 40, RED);

  if (currentState == PAUSE) {
    DrawText("Press Enter to fly!", 100, 600, 40, BLUE);
  } else if (currentState == OVER) {
    DrawText("Game Over!", 100, 600, 75, RED);
    DrawText("Press Enter to try again!", 100, 700, 30, RED);
  } else if (currentState == MENU) {
    RenderMenu();
  }
}

void Renderer::RenderMenu() {
  DrawText("0: Play", 100, 100, 40, BLUE);
  DrawText("1: A.I Type 1", 100, 150, 40, BLUE);
  DrawText("2: A.I Type 2", 100, 200, 40, BLUE);
}