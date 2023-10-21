#include "../inc/NeuralNetwork.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

// constructor
NeuralNetwork::NeuralNetwork(std::vector<float> inputvec, float rate)
    : _inputVector(inputvec), _learningRate(rate), _weightMatrices({}),
      _biasMatrices({}), _aValueMatrices({}) {
  std::random_device device;
  std::mt19937 generator(device());
  std::uniform_real_distribution<> distr(0.0, 1.0);

  // initialize all weights and biases based on inputvec
  for (int k = 0; k < _inputVector.size() - 1; k++) {

    Matrix weightMat(_inputVector[k], _inputVector[k + 1]);
    for (int r = 0; r < weightMat._rows; r++) {
      for (int c = 0; c < weightMat._columns; c++) {
        weightMat.ValueAt(r, c) = distr(generator);
      }
    }
    _weightMatrices.push_back(weightMat);

    Matrix biasMat(1, _inputVector[k + 1]);
    for (int r = 0; r < biasMat._rows; r++) {
      for (int c = 0; c < biasMat._columns; c++) {
        biasMat.ValueAt(r, c) = distr(generator);
      }
    }
    _biasMatrices.push_back(biasMat);
  }
  _aValueMatrices.resize(_inputVector.size());
};

float NeuralNetwork::Sigmoid(float x) { return (1.0f / (1.0 + exp(-x))); };

// derviative of sigmoid
// x = Sigmoid(x) -> sigmoid function will have already been applied to inputs
float NeuralNetwork::Dsigmoid(float x) { return ((x) * (1 - x)); }

bool NeuralNetwork::FeedForward(std::vector<float> trainInputs) {

  // check if inputs has same value as first layer of inputVec
  if (trainInputs.size() != _inputVector[0]) {
    return false;
  }

  // initialize matrix to store values
  Matrix valuesMat(1, trainInputs.size());
  for (int i = 0; i < trainInputs.size(); i++)
    valuesMat._values[i] = trainInputs[i];

  for (int x = 0; x < _weightMatrices.size(); x++) {
    // first matrix is input

    _aValueMatrices[x] = valuesMat;

    valuesMat = valuesMat.DotProduct(_weightMatrices[x]);

    valuesMat = valuesMat.Add(_biasMatrices[x]);

    // go back later and implement applyfunction
    // valuesMat = valuesMat.ApplyFunction(Sigmoid);

    // loop through values mat and apply sigmoid function
    for (int r = 0; r < valuesMat._rows; r++) {
      for (int c = 0; c < valuesMat._columns; c++) {
        valuesMat.ValueAt(r, c) = Sigmoid(valuesMat.ValueAt(r, c));
      }
    };
  };

  // populate last valuesMat to _aValueMatrices
  _aValueMatrices[_weightMatrices.size()] = valuesMat;

  return true;
};

bool NeuralNetwork::FeedBack(std::vector<float> trainOutputs) {

  if (trainOutputs.size() != _inputVector.back()) {
    return false;
  }

  Matrix errors(1, trainOutputs.size());
  errors._values = trainOutputs;

  // solve last layer of errors
  // errors = desired value - calculated value

  Matrix temp = _aValueMatrices.back().ScalarMultiple(-1.0f);
  errors = errors.Add(temp);

  for (int i = _weightMatrices.size() - 1; i >= 0; --i) {

    Matrix temp2 = _weightMatrices[i].Transpose();
    Matrix prevErrors = errors.DotProduct(temp2);

    // apply sigmoid function below
    // Matrix dOutputs = _aValueMatrices[i+1]
    // loop through values mat and apply derivative sigmoid function

    Matrix dOutputs(1, _aValueMatrices[i + 1]._columns);
    for (int r = 0; r < dOutputs._rows; r++) {
      for (int c = 0; c < dOutputs._columns; c++) {
        dOutputs.ValueAt(r, c) = Dsigmoid(_aValueMatrices[i + 1].ValueAt(r, c));
      };
    };

    Matrix dBiases = errors.ElementMultiply(dOutputs);

    dBiases = dBiases.ScalarMultiple(_learningRate);

    Matrix dWeights = _aValueMatrices[i].Transpose().DotProduct(dBiases);

    _weightMatrices[i] = _weightMatrices[i].Add(dWeights);
    _biasMatrices[i] = _biasMatrices[i].Add(dBiases);

    errors = prevErrors;
  }

  return true;
};

std::vector<float> NeuralNetwork::getPredictions() {
  return _aValueMatrices.back()._values;
}
