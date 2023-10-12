#include "../inc/NeuralNetwork.hpp"

//constructor
NeuralNetwork::NeuralNetwork(std::vector<float> inputvec, float rate):
    _inputVector(inputvec),
    _learningRate(rate),
    _weightMatrices({}),
    _biasMatrices({}),
    _aValueMatrices({}) 
    {
        std::random_device device;
        std::mt19937 generator(device());
        std::uniform_real_distribution<> distr(0.0,1.0);

        //initialize all weights and biases based on inputvec
        for(int k = 0; k<_inputVector.size() -1; k++){
            
            Matrix weightMat(_inputVector[k+1], _inputVector[k]);
            for(int r = 0; r <weightMat._rows; r++){
                for(int c= 0; c<weightMat._columns; c++){
                    weightMat.ValueAt(r,c) = distr(generator);
                }
            }
            _weightMatrices.push_back(weightMat);

            Matrix biasMat(_inputVector[k+1], 1);
            for(int r = 0; r <biasMat._rows; r++){
                for(int c= 0; c<biasMat._columns; c++){
                    biasMat.ValueAt(r,c) = distr(generator);
                }
            }
            _biasMatrices.push_back(biasMat);            

        } 

    };