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
    //cout << argc << endl;
    //cout << string(argv[i]).size() << endl;
    //cout << string(argv[i]) + "end";
    cout << myReader.diceCount(string(argv[i])) << endl;
    if(print)
      myReader.printPixelStatus(printScale);
  }
  //DiceReader myReader;
  //cout << myReader.diceCount("dice.png") << endl;
  //myReader.printPixelStatus(10);
  //cout << endl;

  //cout << myReader.diceCount("dice.png") << endl;
  //myReader.printPixelStatus(2);
  //cout << endl;

  //cout << myReader.diceCount("real.png") << endl;
  //myReader.printPixelStatus(10);
  //cout << endl;

  return 0;
}
