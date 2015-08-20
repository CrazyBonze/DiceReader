#include"matrix.h"

/**
 * Matrix::Matrix
 *
 * Constructor for Matrix, sets the size of the 1d array as X*Y
 *
 * @param X the X size of the 2D array
 * @param Y the Y size of the 2D array
 */

Matrix::Matrix(const unsigned int X, const unsigned int Y)
{ 
  _X = X;
  _Y = Y;
  m_Matrix = new unsigned int[ X * Y ];
}

/**
 * Matrix::~Matrix
 *
 * Destructor for Matrix, deletes the array
 */

Matrix::~Matrix()
{ 
  delete m_Matrix;
}

/**
 * Matrix::get
 *
 * Retruns the value stored at position (X,Y)
 *
 * @param X The X value of the value wanted
 * @param Y The Y value of the value wanted
 * @return The value at position (X,Y) in the matrix
 */

int Matrix::get(const unsigned int X, const unsigned int Y)
{ 
  return m_Matrix[getIndex(X,Y)];
}

/**
 * Matrix::set
 *
 * Sets the value at (X,Y) to the value given
 *
 * @param X The X value of the state to set
 * @param Y The Y value of the state to set
 * @param state The vale set at the (X,Y) position in the matrix
 */

void Matrix::set(const unsigned int X, const unsigned int Y, const int state)
{ 
  m_Matrix[getIndex(X,Y)] = state;
}

/**
 * Matrix::fill
 *
 * Fills the entire matrix with a single value
 *
 * @param state The value to set to each position in the matrix
 */

void Matrix::fill(int state)
{ 
  for(unsigned int i = 0; i < _X * _Y; i++)
      m_Matrix[i] = state;
}

/**
 * Matrix::inRange
 *
 * returns TRUE if the (X,Y) is in the range of the matrix
 *
 * @param X The X value to check if it is in range
 * @param Y The Y value to check if it is in range
 * @return True if X and Y are in the range of the matrix
 */

bool Matrix::inRange(unsigned int X, unsigned int Y)
{
  return X < _X && Y < _Y;
}

/**
 * Matrix::getIndex
 *
 * Returns the index of the 1D array given (X,Y) for a 2D matrix
 * 
 * @param X The X value to find the index
 * @param Y The Y value to find the index
 * @return The index of a 1d array given (X,Y)
 */

unsigned int Matrix::getIndex(unsigned int X, unsigned int Y)
{ 
  assert(inRange(X,Y));
  return X * _Y + Y;
}
