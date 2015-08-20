#ifndef DICEREADER_H
#define DICEREADER_H

#include<SFML/Graphics.hpp>
#include"matrix.h"
#include<cmath>
#include<cassert>
#include<algorithm>
#include<string>
#include<iostream>
using namespace std;

class DiceReader {
  public:

    DiceReader();
    ~DiceReader();
    unsigned int diceCount(string);
    void printPixelStatus(unsigned int);

  private:
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
