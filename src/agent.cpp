#include "agent.h"

Agent::Agent(Bird *bird, int type) {
  this->bird = bird;
  this->type = type;
  reset();
}

int Agent::getType() { return this->type; }
void Agent::setType(int type) { this->type = type; }

void Agent::reset() { return; }

void Agent::playType0(std::vector<Pipe *> pipes) {
  if (bird->getPosY() - getCenterPos(pipes) > 20) {
    bird->flap();
  }
}

// The difference between the bird and the gap.
float Agent::getCenterPos(std::vector<Pipe *> pipes) {
  for (Pipe *pipe : pipes) {
    // I made the width of the pipes twice the size of the bird.
    if (bird->getPosX() < pipe->getPosXBot() + 2 * BIRD_WIDTH) {
      return (pipe->getPosYBot() + pipe->getPosYTop() + PIPE_HEIGHT) / 2;
    }
  }
  return 0;
}