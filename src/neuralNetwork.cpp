#include "neuralNetwork.h"

NeuralNetwork::NeuralNetwork(int inputSize, int hiddenSize, int outputSize)
    : inputSize(inputSize), hiddenSize(hiddenSize), outputSize(outputSize) {

  // Initialize weights and biases randomly
  weightsInputHidden.resize(hiddenSize, std::vector<double>(inputSize));
  weightsHiddenOutput.resize(outputSize, std::vector<double>(hiddenSize));
  biasHidden.resize(hiddenSize);
  biasOutput.resize(outputSize);

  // Random initialization
  for (int i = 0; i < hiddenSize; i++) {
    for (int j = 0; j < inputSize; j++) {
      weightsInputHidden[i][j] = randomDouble(-1.0, 1.0);
    }
    biasHidden[i] = randomDouble(-1.0, 1.0);
  }

  for (int i = 0; i < outputSize; i++) {
    for (int j = 0; j < hiddenSize; j++) {
      weightsHiddenOutput[i][j] = randomDouble(-1.0, 1.0);
    }
    biasOutput[i] = randomDouble(-1.0, 1.0);
  }
}

std::vector<double> NeuralNetwork::forward(const std::vector<double> &inputs) {
  // Hidden layer computation
  std::vector<double> hidden(hiddenSize);
  for (int i = 0; i < hiddenSize; i++) {
    double sum = biasHidden[i];
    for (int j = 0; j < inputSize; j++) {
      sum += inputs[j] * weightsInputHidden[i][j];
    }
    hidden[i] = sigmoid(sum); // Activation function
  }

  // Output layer computation
  std::vector<double> output(outputSize);
  for (int i = 0; i < outputSize; i++) {
    double sum = biasOutput[i];
    for (int j = 0; j < hiddenSize; j++) {
      sum += hidden[j] * weightsHiddenOutput[i][j];
    }
    output[i] = sigmoid(sum); // Activation function
  }

  return output;
}

void NeuralNetwork::mutate(double mutationRate, double mutationStrength) {
  // Mutate input-hidden weights
  for (int i = 0; i < hiddenSize; i++) {
    for (int j = 0; j < inputSize; j++) {
      if (randomDouble(0.0, 1.0) < mutationRate) {
        weightsInputHidden[i][j] +=
            randomDouble(-mutationStrength, mutationStrength);
      }
    }
    // Mutate hidden biases
    if (randomDouble(0.0, 1.0) < mutationRate) {
      biasHidden[i] += randomDouble(-mutationStrength, mutationStrength);
    }
  }

  // Mutate hidden-output weights
  for (int i = 0; i < outputSize; i++) {
    for (int j = 0; j < hiddenSize; j++) {
      if (randomDouble(0.0, 1.0) < mutationRate) {
        weightsHiddenOutput[i][j] +=
            randomDouble(-mutationStrength, mutationStrength);
      }
    }
    // Mutate output biases
    if (randomDouble(0.0, 1.0) < mutationRate) {
      biasOutput[i] += randomDouble(-mutationStrength, mutationStrength);
    }
  }
}

double NeuralNetwork::randomDouble(double min, double max) {
  std::uniform_real_distribution<double> distribution(min, max);
  return distribution(generator);
}

NeuralNetwork NeuralNetwork::crossover(const NeuralNetwork &partner) {

  NeuralNetwork child(inputSize, hiddenSize, outputSize); 
  // Crossover input-hidden weights
  for (int i = 0; i < hiddenSize; i++) {
    for (int j = 0; j < inputSize; j++) {
      if (randomDouble(0.0, 1.0) < 0.5) {
        child.weightsInputHidden[i][j] = weightsInputHidden[i][j];
      } else {
        child.weightsInputHidden[i][j] = partner.weightsInputHidden[i][j];
      }
    }
    // Crossover hidden biases
    if (randomDouble(0.0, 1.0) < 0.5) {
      child.biasHidden[i] = biasHidden[i];
    } else {
      child.biasHidden[i] = partner.biasHidden[i];
    }
  }

  // Crossover hidden-output weights
  for (int i = 0; i < outputSize; i++) {
    for (int j = 0; j < hiddenSize; j++) {
      if (randomDouble(0.0, 1.0) < 0.5) {
        child.weightsHiddenOutput[i][j] = weightsHiddenOutput[i][j];
      } else {
        child.weightsHiddenOutput[i][j] = partner.weightsHiddenOutput[i][j];
      }
    }
    // Crossover output biases
    if (randomDouble(0.0, 1.0) < 0.5) {
      child.biasOutput[i] = biasOutput[i];
    } else {
      child.biasOutput[i] = partner.biasOutput[i];
    }
  }

  return child;
}

NeuralNetwork NeuralNetwork::copy() const {
  NeuralNetwork copyNN(inputSize, hiddenSize, outputSize);
  copyNN.weightsInputHidden = weightsInputHidden;
  copyNN.weightsHiddenOutput = weightsHiddenOutput;
  copyNN.biasHidden = biasHidden;
  copyNN.biasOutput = biasOutput;
  return copyNN;
}