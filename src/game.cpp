#include "game.h"

#include <iostream>

Game::Game() {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "bird");
  SetTargetFPS(60);
  SearchAndSetResourceDir("resources");
  Initialize();
}

void Game::Initialize() {
  pipes.clear();
  currentState = PAUSE;
  bird = new Bird();
  pipes.push_back(new Pipe());

  LoadTexture();
  bird->posX = 100;
  bird->posY = WINDOW_HEIGHT / 2;
  score = 0;
  std::cout << "Initialized successfully" << std::endl;
}

Game::~Game() {
  UnloadTexture(backgroundTexture);
  UnloadTexture(birdTexture);
  UnloadTexture(pipeTexture);
  delete bird;
  CloseWindow();
}

void Game::Render() {
  ClearBackground(BLUE);
  DrawTexture(backgroundTexture, 0, 0, WHITE);
  DrawTexture(birdTexture, bird->posX, bird->posY, WHITE);

  for (const auto &pipe : pipes) {
    // Draw pipe at the bottom
    Rectangle srcBottom = {0, 0, (float)PIPE_WIDTH, (float)PIPE_HEIGHT};
    Vector2 posBottom = {(float)pipe->posX, (float)(pipe->posY)};
    DrawTextureRec(pipeTexture, srcBottom, posBottom, WHITE);

    // Draw pipe at the top
    Rectangle srcTop = {0, 0, (float)PIPE_WIDTH, -(float)PIPE_HEIGHT};
    Vector2 posTop = {(float)pipe->posX, (float)(-pipe->spaceWidth)};
    DrawTextureRec(pipeTexture, srcTop, posTop, WHITE);
  }

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

void Game::LoadTexture() {
  Image backgroundImage = LoadImage("game-objects/background-day.png");
  ImageResize(&backgroundImage, WINDOW_WIDTH, WINDOW_HEIGHT);
  backgroundTexture = LoadTextureFromImage(backgroundImage);
  std::cout << "Loaded background texture successfully" << std::endl;
  UnloadImage(backgroundImage);

  Image birdImage = LoadImage("game-objects/yellowbird-midflap.png");
  ImageResize(&birdImage, bird->WIDTH, bird->HEIGHT);
  birdTexture = LoadTextureFromImage(birdImage);
  std::cout << "Loaded bird texture succesfully" << std::endl;
  UnloadImage(birdImage);

  Image pipeImage = LoadImage("game-objects/pipe-green.png");
  ImageResize(&pipeImage, PIPE_WIDTH, PIPE_HEIGHT);
  pipeTexture = LoadTextureFromImage(pipeImage);
  UnloadImage(pipeImage);

  std::cout << "All resources loaded successfully" << std::endl;
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
  while (pipes.back()->posX < -PIPE_WIDTH) {
    pipes.pop_back();
  }
  for (auto &pipe : pipes) {
    pipe->posX -= PIPE_VELOCITY;
  }
}

void Game::HandleInput() {
  if (IsKeyPressed(KEY_SPACE) && currentState == RUN) {
    bird->velocity = -5;
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
  if (bird->posY <= 0 || bird->posY + bird->HEIGHT >= WINDOW_HEIGHT)
    return 1;

  // Pipes collide
  for (const auto &pipe : pipes) {
    Vector2 posBottom = {(float)pipe->posX, (float)(pipe->posY)};
    Vector2 posTop = {(float)pipe->posX, (float)(-pipe->spaceWidth)};

    // Check if posX collide
    if (bird->posX + bird->WIDTH < posBottom.x ||
        bird->posX > posBottom.x + PIPE_WIDTH) {
      continue;
    }

    // Update score
    if (bird->posX >= posBottom.x + PIPE_WIDTH / 2) {
      if (!pipe->scoreIncreased) {
        pipe->scoreIncreased = 1;
        ++score;
      }
    }

    // Check if posY collide
    if (bird->posY + bird->HEIGHT >= posBottom.y ||
        bird->posY <= posTop.y + PIPE_HEIGHT) {
      // std::cout << "Collision detected" << std::endl;
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

    // Manage game state

    if (currentState == RUN) {
      HandleInput();
      UpdateBirdPosition();
      UpdatePipeQueue();
      HandleCollision();
    } else {
      HandleInput();
    }

    BeginDrawing();
    Render();
    EndDrawing();
  }
}