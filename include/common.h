#pragma once
#include <random>

enum GameState { RUN, OVER };
const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 600;
const double GRAVITY = 0.2;
const double ACCEL = 8;
const double PIPE_WIDTH = 52 * 1.5, PIPE_HEIGHT = 320 * 1.5;
const double PIPE_VELOCITY = 7;

double randomDouble(double a, double b, std::mt19937 &gen);