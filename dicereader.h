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

    void printPixleStatus(unsigned int);

  private:

    sf::Image m_Image;
    sf::Vector2u m_ImageSize;

    unsigned int m_DiceTotal;

    //set the PixleStatus matrix to the size of 640x400 to start with
    static const unsigned int X = 640;
    static const unsigned int Y = 400;
    vector<vector<unsigned char> > m_PixleStatus;

    void floodFind();
    unsigned char getPixleStatus(unsigned int, unsigned int);
    void setPixleStatus(unsigned int, unsigned int, unsigned char);
    void clearPixleStatus();
};

#endif
