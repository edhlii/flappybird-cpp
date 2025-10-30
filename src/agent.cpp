#include "agent.h"
#include <iostream>

Agent::Agent(Bird *bird, int type)
    : brain(INPUT_SIZE, HIDDEN_SIZE, OUTPUT_SIZE), fitness(0.0) {
  this->bird = bird;
  this->type = type;
}

Agent::Agent(const NeuralNetwork &brain, Bird *bird, int type)
    : brain(brain.copy()), fitness(0.0) {
  this->bird = bird;
  this->type = type;
}

int Agent::getType() { return this->type; }
double Agent::getFitness() { return this->fitness; }
int Agent::getScore() { return this->score; }

void Agent::setType(int type) { this->type = type; }

void Agent::reset() { return; }

bool Agent::shouldFlap0(std::vector<Pipe *> &pipes) {
  // std::cout << getCenterPos(pipes) << std::endl;
  // std::cout << bird->getPosY() - getCenterPos(pipes) << std::endl;
  if (bird->getPosY() - getCenterPos(pipes) > 20) {
    return true;
  }
  return false;
}

void Agent::playType0(std::vector<Pipe *> &pipes) {
  if (shouldFlap0(pipes) == true) {
    bird->flap();
  }
}

bool Agent::shouldFlap1(std::vector<Pipe *> &pipes) {
  if (bird->isDead())
    return false;
  // Get normalized inputs from game state
  std::vector<double> inputs = {bird->getPosY(), bird->getVelocity()};
  // Neural network forward pass
  std::vector<double> output = brain.forward(inputs);
  // Output is jump probability, jump if > 0.5
  return output[0] > 0.5;
}

void Agent::playType1(std::vector<Pipe *> &pipes) {
  if (shouldFlap1(pipes)) {
    bird->flap();
  }
}

void Agent::addFitness(double reward) { fitness += reward; }

Agent Agent::crossover(const Agent &partner) {
  NeuralNetwork childBrain = brain.crossover(partner.brain);
  return Agent(childBrain, bird, type);
}

void Agent::mutate(double mutationRate, double mutationStrength) {
  brain.mutate(mutationRate, mutationStrength);
}

Agent Agent::copy() const {
  Agent copyAgent(brain.copy(), bird, type);
  copyAgent.fitness = fitness;
  return copyAgent;
}

// The difference between the bird and the gap.
float Agent::getCenterPos(std::vector<Pipe *> &pipes) {
  for (Pipe *pipe : pipes) {
    // I made the width of the pipes twice the size of the bird.
    if (bird->getPosX() < pipe->getPosXBot() + PIPE_WIDTH * 0.65) {
      // std::cout << pipe->getPosYBot() << " " << pipe->getPosYTop() +
      // PIPE_HEIGHT
      //           << std::endl;
      return (pipe->getPosYBot() + pipe->getPosYTop() + PIPE_HEIGHT) / 2;
    }
  }
  return 0;
}