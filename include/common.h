#pragma once
#include <random>

// ---Game constant---

enum GameState { RUN, OVER, PAUSE, MENU };
const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 550;

// const double GRAVITY = 0.2;

const float GRAVITY = 0.2f;
const double PIPE_WIDTH = 52 * 1.75, PIPE_HEIGHT = 320 * 1.75;
const double PIPE_X_VELOCITY = 2.5;
const double PIPE_Y_VELOCITY = 1.5;
const int BIRD_WIDTH = 40;
const int BIRD_HEIGHT = 35;
const int PIPE_SPACING = 200;
const float JUMP_FORCE = 5.0f;

// ---AI constants---

// This means a probability of 1 in 64.
constexpr unsigned short MUTATION_PROBABILITY = 64;
constexpr unsigned char POPULATION_SIZE = 8;
constexpr unsigned char TOTAL_HIDDEN_NODES = 4;
constexpr unsigned char TOTAL_INPUT_NODES = 3;
constexpr unsigned char TOTAL_OUTPUT_NODES = 1;

double randomDouble(double a, double b, std::mt19937& gen);