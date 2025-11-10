#include "game.h"

#include <iostream>

Game::Game() {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "bird");
  SetTargetFPS(60);
  SearchAndSetResourceDir("resources");
  Initialize();
}

void Game::Initialize() {
  aiType = -1;
  groundX1 = 0;
  groundX2 = GROUND_WIDTH;

  pipeManager.reset();
  currentState = MENU;
  bird = new Bird();

  agent0 = new Agent(new Bird(), 0);
  agent0->reset();

  std::mt19937_64 random_engine(
      std::chrono::system_clock::now().time_since_epoch().count());

  agents.resize(POPULATION_SIZE);
  for (int i = 0; i < POPULATION_SIZE; ++i) {
    agents[i] = new Agent(new Bird(), 1);
    agents[i]->generateWeights(random_engine);
  }

  Renderer::LoadAllTexture();
  score = 0;
  std::cout << "Initialized successfully" << std::endl;
}

void Game::UpdateGround() {
  groundX2 -= GROUND_VELOCITY;
  groundX1 -= GROUND_VELOCITY;
  if (groundX1 + GROUND_WIDTH <= 0) {
    groundX1 = groundX2 + GROUND_WIDTH;
  }
  if (groundX2 + GROUND_WIDTH <= 0) {
    groundX2 = groundX1 + GROUND_WIDTH;
  }
  return;
}

void Game::NewGeneration() {
  pipeManager.reset();
  currentState = RUN;
  score = 0;

  for (Agent *agent : agents) {
    agent->bird->reset();
  }

  std::mt19937_64 random_engine(
      std::chrono::system_clock::now().time_since_epoch().count());

  std::sort(agents.begin(), agents.end(), [](Agent *a, Agent *b) {
    return a->getFitness() > b->getFitness();
  });
  Agent *adam, *eva;
  adam = agents[0];
  eva = agents[1];
  agents[2]->crossover(random_engine, adam->getWeights(), eva->getWeights());
  for (int i = 3; i < POPULATION_SIZE; ++i) {
    agents[i]->generateWeights(random_engine);
  }
}

Game::~Game() {
  Renderer::UnloadAllTexture();
  delete bird;
  CloseWindow();
}

void Game::ChooseMode() {
  if (IsKeyPressed(KEY_ZERO)) {
    aiType = -1;
    currentState = PAUSE;
  }
  if (IsKeyPressed(KEY_ONE)) {
    aiType = 0;
    currentState = PAUSE;
  }
  if (IsKeyPressed(KEY_TWO)) {
    aiType = 1;
    currentState = PAUSE;
  }
}

void Game::HandleInput() {
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

  BeginDrawing();
  Renderer::RenderPlayer(bird, pipeManager, currentState, score, maxScore,
                         groundX1, groundX2);
  EndDrawing();
  // Manage game state

  if (currentState == RUN) {
    HandleInput();
    bird->updatePosition();
    pipeManager.updatePipeQueue();
    pipeManager.updatePipePosition();
    UpdateGround();
    HandleCollision(bird);
  } else {
    HandleInput();
  }
}

void Game::RunAgent0() {
  BeginDrawing();
  Renderer::RenderAgent0(agent0, pipeManager, currentState, score, maxScore,
                         groundX1, groundX2);
  EndDrawing();
  // Manage game state
  std::vector<Pipe *> pipes = pipeManager.getPipeList();
  if (currentState == RUN) {
    HandleInput();
    agent0->bird->updatePosition();
    pipeManager.updatePipeQueue();
    pipeManager.updatePipePosition();
    UpdateGround();
    HandleCollision(agent0->bird);
    agent0->playType0(pipes);
  } else {
    HandleInput();
  }
}

void Game::RunAgent1() {
  BeginDrawing();
  Renderer::RenderAgent1(agents, pipeManager, currentState, score, maxScore,
                         groundX1, groundX2);
  EndDrawing();

  // Manage game state
  std::vector<Pipe *> pipes = pipeManager.getPipeList();
  if (currentState == RUN) {
    bool isDead = 1;

    for (Agent *agent : agents) {
      if (agent->bird->isDead())
        continue;
      isDead = 0;
      agent->bird->updatePosition();
      agent->playType1(pipes);
      if (IsCollide(agent->bird)) {
        agent->bird->setDead(true);
      } else {
        agent->addFitness(0.1);
      }
    }

    pipeManager.updatePipeQueue();
    pipeManager.updatePipePosition();
    UpdateGround();

    if (isDead) {
      NewGeneration();
    }

  } else {
    HandleInput();
  }
}

void Game::Menu() {
  ChooseMode();
  return;
}

void Game::Run() {
  while (!WindowShouldClose()) {
    maxScore = std::max(maxScore, score);
    if (currentState == MENU) {
      Menu();
    }
    if (aiType == -1)
      RunPlayer();
    else if (aiType == 0)
      RunAgent0();
    else if (aiType == 1)
      RunAgent1();
  }
}