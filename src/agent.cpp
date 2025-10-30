#include "agent.h"
#include <iostream>

Agent::Agent(Bird *bird, int type) : fitness(0.0), weights(2) {
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
  std::vector<std::vector<float>> neuralNetwork(3);

  neuralNetwork[0].resize(INPUT_SIZE);
  neuralNetwork[1].resize(HIDDEN_SIZE, 0);
  neuralNetwork[2].resize(OUTPUT_SIZE, 0);

  // Input layer.
  neuralNetwork[0][0] = bird->getVelocity();
  neuralNetwork[0][1] = bird->getPosY() - getCenterPos(pipes);

  // Here we're getting the direction of the first 2 pipes, that are in front of
  // the bird.
  // for (Pipe &a : pipes) {
  //   if (x < a.getPosXBot() + 2 * BIRD_SIZE) {
  //     neuralNetwork[0][2] = a.get_direction();

  //     break;
  //   }
  // }

  for (int a = 0; a < neuralNetwork.size() - 1; a++) {
    for (int b = 0; b < neuralNetwork[1 + a].size(); b++) {
      for (int c = 0; c < neuralNetwork[a].size(); c++) {
        neuralNetwork[1 + a][b] += neuralNetwork[a][c] * weights[a][c][b];
      }

      if (neuralNetwork[1 + a][b] <= 0) {
        neuralNetwork[1 + a][b] = pow(2, neuralNetwork[1 + a][b]) - 1;
      } else {
        neuralNetwork[1 + a][b] = 1 - pow(2, -neuralNetwork[1 + a][b]);
      }
    }
  }

  return neuralNetwork[2][0] >= 0;
}

void Agent::playType1(std::vector<Pipe *> &pipes) {
  if (shouldFlap1(pipes)) {
    bird->flap();
  }
}

void Agent::addFitness(double reward) { fitness += reward; }

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

void Agent::crossover(
    std::mt19937_64 &i_random_engine,
    const std::vector<std::vector<std::vector<float>>> &i_bird_0_weights,
    const std::vector<std::vector<std::vector<float>>> &i_bird_1_weights) {
  // I used "Uniform crossover".
  // I think...
  // Hold on, lemme do a quick Google search.
  //(After some time...)
  // Yeah, I was correct.

  for (unsigned char a = 0; a < weights.size(); a++) {
    for (unsigned char b = 0; b < weights[a].size(); b++) {
      for (unsigned char c = 0; c < weights[a][b].size(); c++) {
        // I didn't wanna use random_engine for this.
        // It's like using a katana to cut bread. (Ba dum tss)
        if (0 == rand() % 2) {
          weights[a][b][c] = i_bird_0_weights[a][b][c];
        } else {
          weights[a][b][c] = i_bird_1_weights[a][b][c];
        }

        if (0 == mutationDistribution(i_random_engine)) {
          weights[a][b][c] = weightDistribution(i_random_engine);
        }
      }
    }
  }
}

void Agent::generateWeights(std::mt19937_64 &i_random_engine) {
  weights[0].resize(INPUT_SIZE, std::vector<float>(HIDDEN_SIZE));
  weights[1].resize(HIDDEN_SIZE, std::vector<float>(OUTPUT_SIZE));

  // This is how I structured the vector of weights.
  for (std::vector<std::vector<float>> &layer : weights) {
    for (std::vector<float> &previous_node : layer) {
      for (float &next_node : previous_node) {
        // This is the weight of the connection between the previous node and
        // the next.
        next_node = weightDistribution(i_random_engine);
      }
    }
  }
}