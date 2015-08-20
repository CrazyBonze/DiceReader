#include"matrix.h"

Matrix::Matrix(const unsigned int X, const unsigned int Y)
{ 
  _X = X;
  _Y = Y;
  m_Matrix = new unsigned int[ X * Y ];
}

Matrix::~Matrix()
{ 
  delete m_Matrix;
}

int Matrix::get(const unsigned int X, const unsigned int Y)
{ 
  return m_Matrix[getIndex(X,Y)];
}

void Matrix::set(const unsigned int X, const unsigned int Y, const int state)
{ 
  m_Matrix[getIndex(X,Y)] = state;
}

void Matrix::fill(int state)
{ 
  for(unsigned int i = 0; i < _X * _Y; i++)
      m_Matrix[i] = state;
}

bool Matrix::inRange(unsigned int X, unsigned int Y)
{
  return X < _X && Y < _Y;
}

unsigned int Matrix::getIndex(unsigned int X, unsigned int Y)
{ 
  assert(inRange(X,Y));
  return X * _Y + Y;
}
