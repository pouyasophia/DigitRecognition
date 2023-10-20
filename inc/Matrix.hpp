#pragma once
#include <vector>
#include <functional>

class Matrix{
    public:
    int _rows;
    int _columns;
    std::vector<float> _values;
    Matrix(int rows, int cols): _rows(rows), _columns(cols) {
        _values.resize(_rows*_columns, 0.0f);
    }
    float &ValueAt(int row, int col);
    Matrix Add(Matrix targetMatrix);
    Matrix DotProduct(Matrix targetMatrix);
    Matrix ScalarMultiple(float s);
    Matrix Transpose();
    Matrix ElementMultiply(Matrix targetMatrix);
    //figure out this one later
    //Matrix ApplyFunction(std::function<float(float)> func);
};