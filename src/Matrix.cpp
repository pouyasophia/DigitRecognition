#include "../inc/Matrix.hpp"
#include <cassert>

//taking value of matrix object at a specific row, column
//corresponds to the vector position in values
float &Matrix::ValueAt(int row, int col) {
    return _values[(row * _columns) + col];
}

//Matrix Addition function
Matrix Matrix::Add(Matrix targetMatrix) {
    
    //make sure that matrices have same number of rows and columns
    //std::assert((targetMatrix._rows == _rows));
    Matrix Result(_rows, _columns);
    for (int r = 0; r < _rows; r++){
        for (int c = 0; c<_columns; c++){
            Result.ValueAt(r,c) = ValueAt(r,c) + targetMatrix.ValueAt(r,c); 
        };
    };
    return Result;
};


Matrix Matrix::DotProduct(Matrix targetMatrix){
    
    Matrix Result(_rows, targetMatrix._columns);
    for (int r = 0; r < Result._rows; r++){
        for (int c = 0; c<Result._columns; c++){
            float sum = 0.0f;
            for(int z = 0; z < _columns; z++){
                sum += ValueAt(r,z) * targetMatrix.ValueAt(z,c);
            };
            Result.ValueAt(r,c) = sum; 
        };
    };
    return Result;
};

Matrix Matrix::ScalarMultiple(float s)
{
    Matrix Result(_rows, _columns);
    for (int r = 0; r < _rows; r++){
        for (int c = 0; c<_columns; c++){
            Result.ValueAt(r,c) = ValueAt(r,c)*s; 
        };
    };
    return Result;
};


Matrix Matrix::Transpose(){
    
    Matrix Result(_columns,_rows);
    for (int r = 0; r < _rows; r++){
        for (int c = 0; c < _columns; c++){
            Result.ValueAt(c,r) = ValueAt(r,c); 
        };
    };
    return Result;
};

