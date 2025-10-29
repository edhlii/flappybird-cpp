#pragma once

#include <vector>

#include "bird.h"
#include "common.h"
#include "pipe.h"

class Agent {
 private:
  Bird* bird;
  unsigned fitness;
  unsigned short score;
  std::uniform_int_distribution<int> mutation_distribution;
  // This is the range in which the weights can be.
  std::uniform_real_distribution<float> node_distribution;
  // I didn't know how to use arrays here.
  std::vector<std::vector<std::vector<float>>> weights;

 public:
  Agent();

  bool do_ai_stuff(std::vector<Pipe*> pipes);
  bool isDead();
  bool operator>(Agent& i_bird);
  bool operator<(Agent& i_bird);

  // The difference between the bird and the gap.
  float get_gap_difference(std::vector<Pipe*> pipes);

  unsigned get_fitness();

  unsigned short get_score();

  void crossover(
      std::mt19937_64& i_random_engine,
      const std::vector<std::vector<std::vector<float>>>& i_bird_0_weights,
      const std::vector<std::vector<std::vector<float>>>& i_bird_1_weights);
  void generate_weights(std::mt19937_64& i_random_engine);
  void reset();
  // We'll use i_move to move the bird when it's dead and there are still birds
  // alive.
  // void update(bool i_move, std::vector<Pipe> i_pipes);

  std::vector<std::vector<std::vector<float>>> get_weights();
};