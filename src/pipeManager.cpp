#include "pipeManager.h"

PipeManager::PipeManager() { reset(); }

void PipeManager::reset() {
  pipes.clear();
  pipes.push_back(new Pipe());
}

std::vector<Pipe*> PipeManager::getPipeList() { return pipes; }

void PipeManager::updatePipeQueue() {
  if (pipes.empty() ||
      pipes.back()->getPosXBot() <= WINDOW_WIDTH - PIPE_SPACING) {
    pipes.push_back(new Pipe());
  }
  // if (pipes.back()->getPosX() <= WINDOW_WIDTH - 200) {
  //   pipes.push_back(new Pipe());
  // }

  while (!pipes.empty() && pipes.front()->getPosXBot() < -PIPE_WIDTH) {
    delete pipes.front();
    pipes.erase(pipes.begin());
  }
}

void PipeManager::updatePipePosition() {
  for (Pipe* pipe : pipes) {
    pipe->updatePosition();
  }
}