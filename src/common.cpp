#include "common.h"

double randomDouble(double a, double b, std::mt19937 &gen) {
  std::uniform_real_distribution<double> dist(a, b);
  return dist(gen);
}