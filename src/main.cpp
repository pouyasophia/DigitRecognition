#include "../inc/NeuralNetwork.hpp"
#include <iostream>

int main() {

  // extract mnist training data
  MnistExtractor mnistExt;
  mnistExt.readMnist(
      "/home/sophiapouya/udacity/neuralNetworks/t10k-images.idx3-ubyte");

  // creating neural network
  // 2 input neurons, 3 hidden neurons and 1 output neuron
  std::vector<float> inputVec = {2, 3, 1};
  NeuralNetwork nn(inputVec, .1f);

  // sample dataset
  std::vector<std::vector<float>> targetInputs = {
      {0.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}};
  std::vector<std::vector<float>> targetOutputs = {
      {0.0f}, {0.0f}, {1.0f}, {1.0f}};

  int epoch = 1000;

  // training the neural network with randomized data
  std::cout << "training started\n";

  for (int i = 0; i < epoch; i++) {
    int index = rand() % 4;
    nn.FeedForward(targetInputs[index]);
    nn.FeedBack(targetOutputs[index]);
  }

  std::cout << "training complete\n";

  // testing the neural network
  for (std::vector<float> input : targetInputs) {
    nn.FeedForward(input);
    std::vector<float> predictions = nn.getPredictions();
    std::cout << input[0] << "," << input[1] << " => " << predictions[0]
              << std::endl;
  }

  return 0;
};