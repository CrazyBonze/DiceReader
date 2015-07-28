#include"dicereader.h"

#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;

int main()
{
  sf::Image Image;
  if(!Image.loadFromFile("dice.png"))
    return 1;

  sf::Vector2u image_size;

  image_size = Image.getSize();

  cout << "X=" << image_size.x << endl;
  cout << "Y=" << image_size.y << endl;

  cout << "hello" << endl;
  return 0;
}
