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

    };

    float NeuralNetwork::Sigmoid(float x){
        return (1 / (1 + exp(-x)));
    };

    float NeuralNetwork::Dsigmoid(float x){
        return (NeuralNetwork::Sigmoid(x)*(1 - NeuralNetwork::Sigmoid(x)));
    }

   bool NeuralNetwork::FeedForward(std::vector<float> trainInputs) {

        //check if inputs has same value as first layer of inputVec
        if (trainInputs.size() != _inputVector[0]){
            return false;
        }
        
        //initialize matrix to store values
        Matrix valuesMat(trainInputs.size(),1);
        valuesMat._values = trainInputs;

        for(int x =0; x<_weightMatrices.size(); x++){
            //first matrix is input
            _aValueMatrices[x] = valuesMat;
            valuesMat = valuesMat.DotProduct(_weightMatrices[x]);
            valuesMat = valuesMat.Add(_biasMatrices[x]);
            
            //go back later and implement applyfunction
            //valuesMat = valuesMat.ApplyFunction(Sigmoid);
            
            //loop through values mat and apply sigmoid function
            for(int r = 0; r<valuesMat._rows; r++){
                   valuesMat.ValueAt(r,1) = Sigmoid(valuesMat.ValueAt(r,1)); 
            }
        };

        //populate last valuesMat to _aValueMatrices
        _aValueMatrices[_weightMatrices.size()] = valuesMat;


        return true;
    };

    bool NeuralNetwork::FeedBack(std::vector<float> trainOutputs) {
        
        if(trainOutputs.size() != _inputVector.back()){
            return false;
        }

        Matrix errors(trainOutputs.size(), 1);
        errors._values = trainOutputs;

        //solve last layer of errors
        //errors = desired value - calculated value
        errors = errors.Add(_aValueMatrices.back().ScalarMultiple(-1));

        for(int i = _weightMatrices.size() - 1; i >= 0; --i)  {
            
            Matrix prevErrors = errors.DotProduct(_weightMatrices[i].Transpose());
            
            //apply sigmoid function below
            //Matrix dOutputs = _aValueMatrices[i+1]
            //loop through values mat and apply derivative sigmoid function
            Matrix dOutputs(_aValueMatrices[i+1]._rows, 1);
            for(int r = 0; r<dOutputs._rows; r++){
                   dOutputs.ValueAt(r,1) = Dsigmoid(dOutputs.ValueAt(r,1)); 
            };

            Matrix dbiases = errors.ElementMultiply(dOutputs);
            dbiases = dbiases.ScalarMultiple(_learningRate);
            
            Matrix dweights = _aValueMatrices[i].DotProduct(dbiases);

            _weightMatrices[i] = _weightMatrices[i].Add(dweights);
            _biasMatrices[i] = _biasMatrices[i].Add(dbiases);

            prevErrors = errors;

        }         


        return true;
    };
    
        