#include "../inc/Network.hpp"
#include "../inc/NeuralNetwork.hpp"

int main() {

    //prompt user to enter desired input layer, hidden layer, and output layers
    //std::vector<double> inputVec{2.0, 3.0, 1.0};
    // std::cout<<"Enter the number of input layers in network: ";    
    // std::cin >> inputVec[1];
    // std::cout<<"Enter the number of neurons in second layer: ";
    // std::cin >> inputVec[2];
    // std::cout<<"Enter the number of output layers in network: ";
    // std::cin>> inputVec[3];

    
    //test Matrix Operations
    // int z;
    // Matrix mat1(2, 3);
    // std::cout<<"mat 1:"<<std::endl;
    //     for (int i = 0; i<mat1._rows; i++){
    //         z+=8;
    //         for(int j = 0; j<mat1._columns; j++){
    //             z++;
    //             mat1.ValueAt(i, j) = z + 3;
    //             std::cout<<mat1.ValueAt(i, j)<<" ";
    //         }
    //         std::cout<<""<<std::endl;
    //     }
    // Matrix mat2(2, 3);
    // std::cout<<"mat 2:"<<std::endl;
    //     for (int i = 0; i<mat1._rows; i++){
    //         z+=3;
    //         for(int j = 0; j<mat1._columns; j++){
    //             z++;
    //             mat2.ValueAt(i, j) = z + 2;
    //             std::cout<<mat2.ValueAt(i, j)<<" ";
    //         }
    //         std::cout<<""<<std::endl;
    //     };
    //     for(int k = 0; k<mat1._values.size(); k++){
    //         std::cout<<"Values["<<k<<"]"<<"="<<mat1._values[k]<<std::endl;
    //     }

    //     Matrix results = mat1.Add(mat2);
    //     std::cout<<"Addition"<<std::endl;
    //     for(int r = 0; r<results._rows; r++){
    //         for(int c = 0; c<results._columns; c++){
    //             std::cout<<results.ValueAt(r,c)<<" ";
    //         }
    //         std::cout<<""<<std::endl;
    //     }

    //     Matrix results2 = mat1.ScalarMultiple(4);
    //     std::cout<<"Scalar Multiple"<<std::endl;
    //     for(int r = 0; r<results2._rows; r++){
    //         for(int c = 0; c<results2._columns; c++){
    //             std::cout<<results2.ValueAt(r,c)<<" ";
    //         }
    //         std::cout<<""<<std::endl;
    //     }
        
    //     Matrix results3 = mat1.Transpose();
    //     std::cout<<"Transpose:"<<std::endl;
    //     for(int r = 0; r<results3._rows; r++){
    //         for(int c = 0; c<results3._columns; c++){
    //             std::cout<<results3.ValueAt(r,c)<<" ";
    //         }
    //         std::cout<<""<<std::endl;
    //     }

    //    Matrix results4 = mat1.DotProduct(mat2);
    //    std::cout<<"DotProduct:"<<std::endl;
    //     for(int r = 0; r<results4._rows; r++){
    //         for(int c = 0; c<results4._columns; c++){
    //             std::cout<<results4.ValueAt(r,c)<<" ";
    //         }
    //         std::cout<<""<<std::endl;
    //     }

//test for neural network random number matrices
        NeuralNetwork nn({1,3,4,5,2},5);

        for (int x =0; x<nn._weightMatrices.size(); x++){
            std::cout<<"Weight Matrix ="<<x<<std::endl;
            for(int r =0; r<nn._weightMatrices[x]._rows; r++){
                for(int c =0; c<nn._weightMatrices[x]._columns; c++){
                    std::cout<<nn._weightMatrices[x].ValueAt(r,c)<<" ";
                }
                std::cout<<""<<std::endl;    
            }
        }




        return 0;

};