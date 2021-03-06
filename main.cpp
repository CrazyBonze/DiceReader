#include"dicereader.h"

#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;

int main(int argc, char *argv[])
{
  bool print = false;
  unsigned int printScale;
  if(string(argv[1]) == "-p" || string(argv[1]) == "-print")
  {
    print = true;
    printScale = 10;
  }

  if(argc < 2 + print)
  {
    cerr << "DiceReader needs at least one  image to process." << endl;
    return 1;
  }

  
  DiceReader myReader;
  for(int i = 1 + print; i < argc; i++)
  {
    cout << myReader.diceCount(string(argv[i])) << endl;
    if(print)
      myReader.printPixelStatus(printScale);
  }
  
  return 0;
}
