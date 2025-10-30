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

  agent0->reset();
  agent0 = new Agent(new Bird(), 0);

  std::mt19937_64 random_engine(
      std::chrono::system_clock::now().time_since_epoch().count());
  agents.resize(1);
  for (int i = 0; i < 1; ++i) {
    agents[i] = new Agent(new Bird(), 1);
    agents[i]->generateWeights(random_engine);
  }

  Renderer::LoadAllTexture();
  score = 0;
  std::cout << "Initialized successfully" << std::endl;
}

Game::~Game() {
  Renderer::UnloadAllTexture();
  delete bird;
  CloseWindow();
}

void Game::HandleInput() {
  // if (IsKeyPressed(KEY_ENTER)) {
  //   std::cout << "Enter" << std::endl;
  //   currentState = RUN;
  // }
  if (IsKeyPressed(KEY_SPACE) && currentState == RUN) {
    bird->flap();
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
bool Game::IsCollide(Bird *bird) {
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

void Game::HandleCollision(Bird *bird) {
  bird->setDead(IsCollide(bird));
  if (bird->isDead()) {
    currentState = OVER;
  }
}

void Game::RunPlayer() {
  while (!WindowShouldClose()) {
    // Manage game state

    if (currentState == RUN) {
      HandleInput();
      bird->updatePosition();
      pipeManager.updatePipeQueue();
      pipeManager.updatePipePosition();
      HandleCollision(bird);
      // agent.play(pipeManager.getPipeList());
    } else {
      HandleInput();
    }

    BeginDrawing();
    Renderer::RenderPlayer(bird, pipeManager, currentState, score);
    // Renderer::RenderAI(&agent, pipeManager, currentState, score);
    EndDrawing();
  }
}

void Game::RunAgent0() {
  while (!WindowShouldClose()) {
    // Manage game state
    std::vector<Pipe *> pipes = pipeManager.getPipeList();
    if (currentState == RUN) {
      HandleInput();
      agent0->bird->updatePosition();
      pipeManager.updatePipeQueue();
      pipeManager.updatePipePosition();
      HandleCollision(agent0->bird);
      agent0->playType0(pipes);
    } else {
      HandleInput();
    }

    BeginDrawing();
    Renderer::RenderAgent0(agent0, pipeManager, currentState, score);
    EndDrawing();
  }
}

void Game::RunAgent1() {

  while (!WindowShouldClose()) {
    // Manage game state
    std::vector<Pipe *> pipes = pipeManager.getPipeList();
    if (currentState == RUN) {
      HandleInput();
      for (Agent *agent : agents) {
        agent->bird->updatePosition();
        agent->playType1(pipes);
        HandleCollision(agent->bird);
      }
      pipeManager.updatePipeQueue();
      pipeManager.updatePipePosition();

    } else {
      HandleInput();
    }

    BeginDrawing();
    Renderer::RenderAgent1(agents, pipeManager, currentState, score);
    EndDrawing();
  }
}