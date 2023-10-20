#include "Matrix.hpp"
#include <random>

class NeuralNetwork {
public:
  std::vector<Matrix> _weightMatrices;
  std::vector<Matrix> _biasMatrices;
  std::vector<Matrix> _aValueMatrices;
  std::vector<float> _inputVector;
  float _learningRate;
  NeuralNetwork(std::vector<float> inputvec, float rate);
  float Sigmoid(float x);
  float Dsigmoid(float x);
  bool FeedForward(std::vector<float> inputs);
  bool FeedBack(std::vector<float> outputs);
  std::vector<float> getPredictions();
};