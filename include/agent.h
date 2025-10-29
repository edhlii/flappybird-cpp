#pragma once

#include <random>
#include <vector>

#include "bird.h"
#include "common.h"
#include "pipe.h"

class Agent {
private:
  int type;
  int fitness;
  int score;
  std::uniform_int_distribution<int> mutationDistribution;
  std::uniform_real_distribution<float> weightDistribution;

public:
  Agent(Bird *bird, int type);
  Bird *bird;
  int getType();
  // int getFitness();
  // int getScore();
  float getCenterPos(std::vector<Pipe *> pipes);

  void setType(int type);

  void playType0(std::vector<Pipe *> pipes);
  // void playType1(std::vector<Pipe *> pipes);
  void reset();
};