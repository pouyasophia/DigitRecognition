#include "../inc/Matrix.hpp"
#include <cassert>
#include <iostream>

// taking value of matrix object at a specific row, column
// corresponds to the vector position in values
float &Matrix::ValueAt(int row, int col) {
  return _values[(col * _rows) + row];
}

// Matrix Addition function
Matrix Matrix::Add(Matrix &targetMatrix) {

  // make sure that matrices have same number of rows and columns
  assert((targetMatrix._rows == _rows));

  Matrix Result(_rows, _columns);
  for (int r = 0; r < _rows; r++) {
    for (int c = 0; c < _columns; c++) {
      Result.ValueAt(r, c) = ValueAt(r, c) + targetMatrix.ValueAt(r, c);
    };
  };
  return Result;
};

Matrix Matrix::DotProduct(Matrix &targetMatrix) {

  // make sure the columns the first matrix = rows of second matrix
  assert(_columns == targetMatrix._rows);

  Matrix Result(_rows, targetMatrix._columns);
  for (int r = 0; r < Result._rows; r++) {
    for (int c = 0; c < Result._columns; c++) {
      float sum = 0.0f;
      for (int z = 0; z < _columns; z++) {
        sum += ValueAt(r, z) * targetMatrix.ValueAt(z, c);
      };
      Result.ValueAt(r, c) = sum;
    };
  };
  return Result;
};

Matrix Matrix::ScalarMultiple(float s) {
  Matrix Result(_rows, _columns);
  for (int r = 0; r < _rows; r++) {
    for (int c = 0; c < _columns; c++) {
      Result.ValueAt(r, c) = ValueAt(r, c) * s;
    };
  };
  return Result;
};

Matrix Matrix::Transpose() {

  Matrix Result(_columns, _rows);
  for (int r = 0; r < _rows; r++) {
    for (int c = 0; c < _columns; c++) {
      Result.ValueAt(c, r) = ValueAt(r, c);
    };
  };
  return Result;
};

// Matrix Matrix::ApplyFunction(std::function<float(float)> func){

//     //define an output matrix that's the same size as input to function
//     Matrix output(_rows,_columns);

//     //loop through matrix to apply function at every row,column pair
//     for(int r=0; r<_rows; r++){
//         for(int c=0; c<_columns; c++){
//             output.ValueAt(r,c) = func(ValueAt(r,c));
//         }
//     }
//     return output;
// };

// Hadamard Product
Matrix Matrix::ElementMultiply(Matrix &targetMatrix) {

  // check if matrices are same dimensions-> requirement for Hadamard product

  assert(targetMatrix._rows == _rows && targetMatrix._columns == _columns);

  Matrix results(_rows, _columns);
  for (int r = 0; r < _rows; ++r) {
    for (int c = 0; c < _columns; ++c) {
      results.ValueAt(r, c) = ValueAt(r, c) * targetMatrix.ValueAt(r, c);
    }
  }
  return results;
};

void Matrix::printMatrix() {
  for (int r = 0; r < _rows; ++r) {
    for (int c = 0; c < _columns; ++c) {
      std::cout << ValueAt(r, c) << " ";
    }
    std::cout << "\n";
  }
};