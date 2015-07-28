#ifndef DICEREADER_H
#define DICEREADER_H

#include<SFML/Graphics.hpp>

#include<string>
#include<iostream>
using namespace std;

class DiceReader {
  public:

    DiceReader();

    unsigned int diceCount(string);

  private:

    sf::Image Image;
    sf::Vector2u imageSize;

    unsigned int diceTotal;
    void floodFind();
};

#endif
