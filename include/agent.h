#pragma once

#include <random>
#include <vector>

#include "bird.h"
#include "common.h"
#include "pipe.h"

class Agent {
private:
  static const int INPUT_SIZE = 2;
  static const int HIDDEN_SIZE = 8;
  static const int OUTPUT_SIZE = 1;
  int type;
  double fitness;
  int score;
  std::uniform_int_distribution<int> mutationDistribution;
  std::uniform_real_distribution<float> weightDistribution;
  std::vector<std::vector<std::vector<float>>> weights;

public:
  Agent(Bird *bird, int type);
  Bird *bird;
  int getType();
  double getFitness();
  int getScore();
  float getCenterPos(std::vector<Pipe *> &pipes);

  void setType(int type);

  bool shouldFlap0(std::vector<Pipe *> &pipes);
  void playType0(std::vector<Pipe *> &pipes);
  bool shouldFlap1(std::vector<Pipe *> &pipes);
  void playType1(std::vector<Pipe *> &pipes);

  void crossover(
      std::mt19937_64 &i_random_engine,
      const std::vector<std::vector<std::vector<float>>> &i_bird_0_weights,
      const std::vector<std::vector<std::vector<float>>> &i_bird_1_weights);

  void generateWeights(std::mt19937_64 &i_random_engine);

  void addFitness(double reward);
  // void mutate(double mutationRate = 0.1, double mutationStrength = 0.3);
  // Agent copy() const;

  void reset();
};