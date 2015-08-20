#ifndef MATRIX_H_
#define MATRIX_H_

#include <cassert>

class Matrix {
  public:
    Matrix(const unsigned int X, const unsigned int Y);
    ~Matrix();
    int get(const unsigned int X, const unsigned int Y);
    void set(const unsigned int X, const unsigned int Y, const int state);
    void fill(int state);
    bool inRange(unsigned int X, unsigned int Y);
  private:
    unsigned int _X;
    unsigned int _Y;
    unsigned int *m_Matrix;
    unsigned int getIndex(unsigned int X, unsigned int Y);
};

#endif  // MATRIX_H_
