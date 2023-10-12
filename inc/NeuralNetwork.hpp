#include <random>
#include "Matrix.hpp"

class NeuralNetwork {
public:
std::vector<Matrix> _weightMatrices;
std::vector<Matrix> _biasMatrices;
std::vector<Matrix> _aValueMatrices;
std::vector<float> _inputVector;
float _learningRate;
NeuralNetwork(std::vector<float> inputvec, float rate);
};