#ifndef DICEREADER_H
#define DICEREADER_H

#include<SFML/Graphics.hpp>

#include<cmath>
#include<cassert>
#include<algorithm>
#include<string>
#include<iostream>
using namespace std;

class DiceReader {
  public:

    DiceReader();
    ~DiceReader()
    { delete m_PixelState;}
    unsigned int diceCount(string);
    void printPixelStatus(unsigned int);

  private:
    //Member classes
    class Matrix {
      public:
        Matrix(const unsigned int X, const unsigned int Y)
        { _X = X; _Y = Y; m_Matrix = new unsigned int[ X * Y ];}
        ~Matrix()
        { delete m_Matrix;}
        unsigned char get(const unsigned int X, const unsigned int Y)
        { return m_Matrix[getIndex(X,Y)];}
        void set(const unsigned int X, const unsigned int Y, 
            const unsigned char s)
        { m_Matrix[getIndex(X,Y)] = s;}
        void fill(unsigned char state)
        { for(unsigned int i = 0; i < _X * _Y; i++)
          m_Matrix[i] = state;}
        //const unsigned int _X;
        //const unsigned int _Y;
        unsigned int _X;
        unsigned int _Y;
      private:
        unsigned int *m_Matrix;
        unsigned int getIndex(unsigned int X, unsigned int Y)
        { return _X * Y + X + 1;}
    };

    //Member Variables
    Matrix *m_PixelState;

    //color of the pip
    sf::Color m_Color;
    static const double PERCENT_DIF;

    //the image of the dice
    sf::Image m_Image;
    sf::Vector2u m_ImageSize;

    unsigned int m_DiceTotal;

    //set the PixleStatus matrix to the size of 640x400 to start with
    unsigned int m_X, m_Y;

    //Private Member Functions
    void resizePixelStatus(unsigned int, unsigned int);
    void floodFind(unsigned int, unsigned int);
    bool pixelCompare(sf::Color, sf::Color, double);
    void pipFiller(unsigned int, unsigned int);
};

#endif
