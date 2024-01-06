#include "../inc/NeuralNetwork.hpp"
#include <iostream>

int main() {

  // extract mnist training data
  MnistExtractor mnistExt;
  // mnistExt.readMnistImage("../t10k-images.idx3-ubyte");
  // mnistExt.readMnistLabel("../t10k-labels.idx1-ubyte");
  mnistExt.readMnistImage("../train-images.idx3-ubyte");
  mnistExt.readMnistLabel("../train-labels.idx1-ubyte");

  // creating neural network
  // 2 input neurons, 3 hidden neurons and 1 output neuron
  std::vector<float> inputVec = {2, 3, 1};
  NeuralNetwork nn(inputVec, .1f);

  std::vector<float> inputVec2 = {784, 3, 1};
  NeuralNetwork nn2(inputVec2, 3.0f);

  // sample dataset
  std::vector<std::vector<float>> targetInputs = {
      {0.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}};
  std::vector<std::vector<float>> targetOutputs = {
      {0.0f}, {0.0f}, {1.0f}, {1.0f}};

  std::vector<float> digitsInputs = mnistExt.getImages();

  // make a vector of vectors for input digits
  std::vector<std::vector<float>> imagesMnist;

  std::vector<float> tempVec;
  for (int i = 0; i < digitsInputs.size(); ++i) {
    int k;
    if (i % 784 == 0 && i > 0) {
      tempVec.emplace_back(digitsInputs[i]);
      k = 0;
    }

    else {
      k++;
      if (k == 783) {
        imagesMnist.emplace_back(tempVec);
        tempVec.clear();
      }
      tempVec.emplace_back(digitsInputs[i]);
    };
  }

  std::vector<float> digitsOutputs = mnistExt.getLabels();
  std::vector<std::vector<float>> labelsMnist;

  for (int i = 0; i < digitsOutputs.size(); ++i) {
    std::vector<float> tempvec;
    tempvec.push_back(digitsOutputs[i]);
    labelsMnist.push_back(tempvec);
    tempvec.clear();
  }

  std::cout << "size of labels data set =" << labelsMnist.size() << std::endl;
  int epoch = 10;
  int epoch2 = 10;

  // training the neural network with randomized data
  std::cout << "training for xor gate started\n";

  for (int i = 0; i < epoch; i++) {
    int index = rand() % 4;
    nn.FeedForward(targetInputs[index]);
    nn.FeedBack(targetOutputs[index]);
  }
  std::cout << "training for xor gate complete\n";

  std::cout << "training for dig recognition started\n";
  // for the length of the epoch
  for (int j = 0; j < epoch2; ++j) {

    // choose random number for 60k of images
    int ind = rand() % 60000;

    // apply feed forward to the image
    nn2.FeedForward(imagesMnist[ind]);

    // apply feed back to the image
    nn2.FeedBack(labelsMnist[ind]);

    // apply feed back to the corresponding label
  }
  std::cout << "training for dig recognition complete\n";

  // testing the neural network
  for (std::vector<float> input : targetInputs) {
    nn.FeedForward(input);
    std::vector<float> predictions = nn.getPredictions();
    std::cout << input[0] << "," << input[1] << " => " << predictions[0]
              << std::endl;
  }

  // testing dig recognition for first 15 images
  for (int k = 0; k < 4; ++k) {
    nn2.FeedBack(imagesMnist[k]);
    nn2.FeedBack(labelsMnist[k]);
    std::vector<float> predictions2 = nn2.getPredictions();
    std::cout << "image" << k << " =>" << predictions2[0] << std::endl;
  }

  return 0;
};