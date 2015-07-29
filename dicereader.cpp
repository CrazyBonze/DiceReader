#include"dicereader.h"

/**
 * DiceReader::DiceReader
 *
 * Constructor for DiceReader
 */

DiceReader::DiceReader()
{
  m_DiceTotal = 0;//set to 0 because we have not counted anything
  m_PixleStatus.resize( Y, vector<unsigned char>( X, 0));//fill status with 0
}

/**
 * DiceReader::diceCount
 *
 * Parses through an image to find the number represented on a dice
 *
 * @param imageName The name of the image to process
 * @return The unsigned int value represented by the dice
 */

unsigned int DiceReader::diceCount(string imageName)
{
  clearPixleStatus();
  m_DiceTotal = 0;
  if(!m_Image.loadFromFile(imageName))
  {
    cerr << "ERROR: Could not load image from disk!" << endl;
    return m_DiceTotal;
  }

  m_ImageSize = m_Image.getSize();

  //for tesintg
  cout << "X= " << m_ImageSize.x << endl;
  cout << "Y= " << m_ImageSize.y << endl;

  for(unsigned int i = 10; i <= 30; i++)
    for(unsigned int k = 10; k <= 30; k++)
      setPixleStatus( i, k, 2);
  setPixleStatus( 50, 40, 2);

  cout << "status at (50,40) = " << int(getPixleStatus(50,40)) << endl;
  //end of testing

  return m_DiceTotal;
}

/**
 * DiceReader::printPixleStatus
 *
 * prints the status of the pixles to the screen
 *
 * @param scale The scale wich the m_PixleStatus matrix will be printed in
 */

void DiceReader::printPixleStatus(unsigned int scale)
{
  for(vector<vector<unsigned char> >::iterator it1 = m_PixleStatus.begin();
      it1 != m_PixleStatus.end(); it1+=scale)
  {
    for(vector<unsigned char>::iterator it2 = it1->begin();
        it2 != it1->end(); it2+=scale)
    {
      cout << int(*it2);
    }
    cout << endl;
  }
}

/**
 * DiceReader::floodFind
 *
 * Recursive flood fill modified to find the pips on one of the six 
 * sides of a common dice. It marks each pixle as read until it find one of
 * the darker pixles representing the pips of a die. When it finds a pip pixle
 * it passes to pipFiller to mark tose pixles as read and ads one to diceTotal.
 */

void DiceReader::floodFind()
{

}

/**
 * DiceReader::getPixleStatus
 *
 * Gets the status value of the pixle at (x,y)
 *
 * @param X The x value for the pixle location
 * @param Y The y value for the pixle location
 * @return The status of the pixle; 
 *  0 - untouched
 *  1 - touched normal pixle
 *  2 - touched pip pixle
 */

unsigned char DiceReader::getPixleStatus(unsigned int X, unsigned int Y)
{
  assert(X < m_ImageSize.x && Y < m_ImageSize.y);
  return m_PixleStatus[X][Y];
}

/**
 * DiceReader::setPixleStatus
 *
 * Sets the status of the pixle at (x,y). Throws an assertion
 * if the value snt is not in its range.
 *
 * @param X The x value for the pixle location
 * @param Y The y value for the pixle location
 * @param The status of the pixle;
 *  0 - untouched
 *  1 - touched normal pixle
 *  2 - touched pip pixle
 */

void DiceReader::setPixleStatus(unsigned int X, unsigned int Y, unsigned char status)
{
  assert( status <= 2);//check to see if it is in range
  assert(X < m_ImageSize.x && Y < m_ImageSize.y);
  m_PixleStatus[X][Y] = status;
}

/**
 * DiceReader::clearPixleStatus
 *
 * Sets m_PixleStatus contents to the value of 0.
 */

void DiceReader::clearPixleStatus()
{
  for(vector<vector<unsigned char> >::iterator it = m_PixleStatus.begin();
      it != m_PixleStatus.end(); it++)
  {
    fill(it->begin(), it->end(), 0);
  }
}
