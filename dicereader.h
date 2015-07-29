#ifndef DICEREADER_H
#define DICEREADER_H

#include<SFML/Graphics.hpp>

#include<cassert>
#include<algorithm>
#include<vector>
#include<string>
#include<iostream>
using namespace std;

class DiceReader {
  public:

    DiceReader();

    unsigned int diceCount(string);

    void printPixelStatus(unsigned int);

  private:
    sf::Color m_Color;

    sf::Image m_Image;
    sf::Vector2u m_ImageSize;

    unsigned int m_DiceTotal;

    //set the PixleStatus matrix to the size of 640x400 to start with
    static const unsigned int X = 640;
    static const unsigned int Y = 400;
    vector<vector<unsigned char> > m_PixelStatus;

    void floodFind(unsigned int, unsigned int);
    void pipFiller(unsigned int, unsigned int);
    unsigned char getPixelStatus(unsigned int, unsigned int);
    void setPixelStatus(unsigned int, unsigned int, unsigned char);
    void clearPixelStatus();
};

#endif
