#include "agent.h"

Agent::Agent()
    : mutation_distribution(0, MUTATION_PROBABILITY - 1),
      node_distribution(-1, std::nextafter(1, 2)),
      weights(2) {
  reset();
}

bool Agent::do_ai_stuff(std::vector<Pipe*> pipes) {
  std::vector<std::vector<float>> neural_network(3);

  neural_network[0].resize(TOTAL_INPUT_NODES);
  neural_network[1].resize(TOTAL_HIDDEN_NODES, 0);
  neural_network[2].resize(TOTAL_OUTPUT_NODES, 0);

  // Input layer.
  neural_network[0][0] = bird->getVelocity();
  neural_network[0][1] = get_gap_difference(pipes);

  // Here we're getting the direction of the first 2 pipes, that are in front of
  // the bird.
  //   for (Pipe& a : pipes) {
  //     if (bird->getPosX() < a.getPosX() + 2 * BIRD_WIDTH) {
  //       neural_network[0][2] = a.get_direction();
  //       break;
  //     }
  //   }

  // I heard that smart people use matrices in a neural network.
  // But I'm not one of them.
  for (unsigned char a = 0; a < neural_network.size() - 1; a++) {
    for (unsigned char b = 0; b < neural_network[1 + a].size(); b++) {
      for (unsigned char c = 0; c < neural_network[a].size(); c++) {
        neural_network[1 + a][b] += neural_network[a][c] * weights[a][c][b];
      }

      if (0 >= neural_network[1 + a][b]) {
        neural_network[1 + a][b] = pow(2, neural_network[1 + a][b]) - 1;
      } else {
        neural_network[1 + a][b] = 1 - pow(2, -neural_network[1 + a][b]);
      }
    }
  }

  return 0 <= neural_network[2][0];
}

bool Agent::isDead() { return bird->isDead(); }
bool Agent::operator>(Agent& i_bird) {
  return get_fitness() > i_bird.get_fitness();
}
bool Agent::operator<(Agent& i_bird) {
  return get_fitness() < i_bird.get_fitness();
}

// The difference between the bird and the gap.
float Agent::get_gap_difference(std::vector<Pipe*> pipes) {
  for (Pipe* pipe : pipes) {
    // I made the width of the pipes twice the size of the bird.
    if (bird->getPosX() < pipe->getPosXBot() + 2 * BIRD_WIDTH) {
      return (pipe->getPosYBot() + pipe->getPosYTop() + PIPE_HEIGHT) / 2;
    }
  }

  return 0;
}

unsigned Agent::get_fitness() { return fitness; }

unsigned short Agent::get_score() { return score; }

void Agent::crossover(
    std::mt19937_64& i_random_engine,
    const std::vector<std::vector<std::vector<float>>>& i_bird_0_weights,
    const std::vector<std::vector<std::vector<float>>>& i_bird_1_weights) {
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

        if (0 == mutation_distribution(i_random_engine)) {
          weights[a][b][c] = node_distribution(i_random_engine);
        }
      }
    }
  }
}

void Agent::generate_weights(std::mt19937_64& i_random_engine) {
  weights[0].resize(TOTAL_INPUT_NODES, std::vector<float>(TOTAL_HIDDEN_NODES));
  weights[1].resize(TOTAL_HIDDEN_NODES, std::vector<float>(TOTAL_OUTPUT_NODES));

  // This is how I structured the vector of weights.
  for (std::vector<std::vector<float>>& layer : weights) {
    for (std::vector<float>& previous_node : layer) {
      for (float& next_node : previous_node) {
        // This is the weight of the connection between the previous node and
        // the next.
        next_node = node_distribution(i_random_engine);
      }
    }
  }
}
void Agent::reset() {
  bird->reset();
  fitness = 0;
  score = 0;
}

std::vector<std::vector<std::vector<float>>> Agent::get_weights() {
  return weights;
}