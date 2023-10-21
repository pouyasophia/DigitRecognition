#include <functional>
#include <vector>

class Matrix {

public:
  // constructor with rows and columns
  Matrix(int rows, int cols) : _rows(rows), _columns(cols) {
    _values.resize(_rows * _columns, 0.0f);
  }

  // default constructor
  Matrix() : _rows(0), _columns(0), _values({}){};

  float &ValueAt(int row, int col);
  Matrix Add(Matrix &targetMatrix);
  Matrix DotProduct(Matrix &targetMatrix);
  Matrix ScalarMultiple(float s);
  Matrix Transpose();
  Matrix ElementMultiply(Matrix &targetMatrix);
  void printMatrix();
  int getRows() { return _rows; };
  void setRows(int rows) { _rows = rows; };
  int getCols() { return _columns; };
  void setCols(int cols) { _columns = cols; }
  std::vector<float> getValues() { return _values; };
  void setValues(std::vector<float> vals) { _values = vals; }

private:
  int _rows;
  int _columns;
  std::vector<float> _values;
};