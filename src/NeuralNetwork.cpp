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
            
            Matrix weightMat(_inputVector[k], _inputVector[k+1]);
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

        //initialize the value matrix to be same size as input vec?
        //_aValueMatrices.resize(_inputVector.size());


    };

    float NeuralNetwork::Sigmoid(float x){
        return (1 / (1 + exp(-x)));
    };

   bool NeuralNetwork::FeedForward(std::vector<float> inputs) {

        //check if inputs has same value as first layer of inputVec
        if (inputs.size() != _inputVector.size()){
            return false;
        }
        
        //initialize matrix to store values
        Matrix valuesMat(inputs.size(),1);
        valuesMat._values = inputs;

        for(int x =0; x<_weightMatrices.size(); x++){
            //first matrix is input
            _aValueMatrices[x] = valuesMat;
            valuesMat = valuesMat.DotProduct(_weightMatrices[x]);
            valuesMat = valuesMat.Add(_biasMatrices[x]);
            
            //go back later and implement applyfunction
            //valuesMat = valuesMat.ApplyFunction(Sigmoid);
            
            //loop through values mat and apply sigmoid function
            for(int r = 0; r<_aValueMatrices[x]._rows; r++){
                for(int c=0; c<_aValueMatrices[x]._columns; c++){
                   _aValueMatrices[x].ValueAt(r,c) = Sigmoid(_aValueMatrices[x].ValueAt(r,c)); 
                }
            }
        };

        //populate last valuesMat to _aValueMatrices
        _aValueMatrices[_weightMatrices.size()] = valuesMat;


        return true;
    };
    
        