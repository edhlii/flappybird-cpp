#pragma once
#include <cmath>
#include <random>
#include <vector>

class NeuralNetwork {
private:
  std::vector<std::vector<double>> weightsInputHidden;
  std::vector<std::vector<double>> weightsHiddenOutput;
  std::vector<double> biasHidden;
  std::vector<double> biasOutput;

  int inputSize, hiddenSize, outputSize;
  std::default_random_engine generator;

  double sigmoid(double x) { return 1.0 / (1.0 + exp(-x)); }

  double randomDouble(double min, double max);

public:
  NeuralNetwork(int inputSize, int hiddenSize, int outputSize);

  // Forward propagation
  std::vector<double> forward(const std::vector<double> &inputs);

  // Genetic operations
  void mutate(double mutationRate, double mutationStrength);
  NeuralNetwork crossover(const NeuralNetwork &partner);

  // Getters for serialization (optional)
  std::vector<double> getFlattenedWeights() const;
  void setFromFlattenedWeights(const std::vector<double> &weights);

  // Utility
  NeuralNetwork copy() const;
};