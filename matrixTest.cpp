#include"matrix.h"
#include<iostream>
using namespace std;

int main()
{
  Matrix *matrix;
  matrix = new Matrix(10,10);
  matrix->set(2,2,6);
  cout << matrix->get(2,2) << endl;
  unsigned int X = 10, Y = 12;
  Matrix myMatrix = Matrix(5,5);
  myMatrix.set(2,2,6);
  cout << myMatrix.get(2,2) << endl;
  Matrix newMatrix = Matrix(X,Y);
  unsigned int count = 0;
  for(unsigned int i = 0; i < X; i++)
  {
    for(unsigned int j = 0; j < Y; j++)
    {
      newMatrix.set(i,j,count);
      count++;
    }
  }
  
  for(unsigned int i = 0; i < X; i++)
  {
    for(unsigned int j = 0; j < Y; j++)
    {
      cout << newMatrix.get(i,j) << ',';
    }
    cout << endl;
  }


  return 0;
}
