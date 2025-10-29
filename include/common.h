#pragma once
#include <random>

// ---Game constant---

enum GameState { RUN, OVER, PAUSE, MENU };
const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 550;

// const double GRAVITY = 0.2;

const float GRAVITY = 0.4f;
const double PIPE_WIDTH = 52 * 2, PIPE_HEIGHT = 320 * 2;
const double PIPE_X_VELOCITY = 5.5;
const double PIPE_Y_VELOCITY = 1.5;
const int BIRD_WIDTH = 40 * 1.7;
const int BIRD_HEIGHT = 35 * 1.7;
const int PIPE_SPACING = 200;
const float JUMP_FORCE = 7.5f;
const float GROUND_WIDTH = 336 * 2;
const float GROUND_HEIGHT = 112 * 1.15;

const float PIPE_GAP = 200; // Space between top and bottom pipe
const float MAX_PIPE_Y = WINDOW_HEIGHT - GROUND_HEIGHT - 50.0;
const float MIN_PIPE_Y = 50.0 + PIPE_GAP;

// ---AI constants---

// This means a probability of 1 in 64.
constexpr unsigned short MUTATION_PROBABILITY = 64;
constexpr unsigned char POPULATION_SIZE = 8;
constexpr unsigned char TOTAL_HIDDEN_NODES = 4;
constexpr unsigned char TOTAL_INPUT_NODES = 3;
constexpr unsigned char TOTAL_OUTPUT_NODES = 1;

double randomDouble(double a, double b, std::mt19937 &gen);