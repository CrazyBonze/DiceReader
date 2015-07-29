#include"dicereader.h"

/**
 * DiceReader::DiceReader
 *
 * Constructor for DiceReader
 */

DiceReader::DiceReader()
{
  m_Color = sf::Color::Black;
  m_DiceTotal = 0;//set to 0 because we have not counted anything
  m_PixelStatus.resize( X, vector<unsigned char>( Y, 0));//fill status with 0
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
  clearPixelStatus();
  m_DiceTotal = 0;
  if(!m_Image.loadFromFile(imageName))
  {
    cerr << "ERROR: Could not load image from disk!" << endl;
    return m_DiceTotal;
  }

  m_ImageSize = m_Image.getSize();

  //for tesintg
  /**
  cout << "X= " << m_ImageSize.x << endl;
  cout << "Y= " << m_ImageSize.y << endl;

  for(unsigned int i = 10; i <= 30; i++)
    for(unsigned int k = 10; k <= 30; k++)
      setPixelStatus( i, k, 2);
  setPixelStatus( 0, 0, 1);
  setPixelStatus( 639, 0, 2);
  setPixelStatus( 0, 399, 2);
  setPixelStatus( 639, 399, 2);

  cout << "status at (50,40) = " << int(getPixelStatus(50,40)) << endl;
  */
  //end of testing
  //sf::Color mycolor = m_Image.getPixel(0,0);
  floodFind( 300, 210);

  return m_DiceTotal;
}

/**
 * DiceReader::printPixelStatus
 *
 * prints the status of the pixles to the screen
 *
 * @param scale The scale wich the m_PixelStatus matrix will be printed in
 */

void DiceReader::printPixelStatus(unsigned int scale)
{
  for(vector<vector<unsigned char> >::iterator it1 = m_PixelStatus.begin();
      it1 != m_PixelStatus.end(); it1+=scale)
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
 * sides of a common dice. It marks each pixel as read until it find one of
 * the darker pixels representing the pips of a die. When it finds a pip pixel
 * it passes to pipFiller to mark tose pixels as read and ads one to diceTotal.
 */

void DiceReader::floodFind(unsigned int X, unsigned int Y)
{
  if(X >= m_ImageSize.x || Y >= m_ImageSize.y)
    return;
  if(getPixelStatus( X, Y) > 0)
    return;
  if(m_Image.getPixel( X, Y) != m_Color)
  {
    setPixelStatus( X, Y, 1);
  }
  else
  {
    m_DiceTotal++;
    pipFiller( X, Y);
    //setPixelStatus( X, Y, 2);
  }

  floodFind( X + 1, Y);
  floodFind( X, Y + 1);
  floodFind( X - 1, Y);
  floodFind( X, Y - 1);

  return;
}

/**
 * DiceReader::pipFiller
 *
 * Marks the pixels of a found pip as read
 *
 * @param X The x value of the pixel representing part of a pip
 * @param Y The y value of the pixel representing part of a pip
 */

void DiceReader::pipFiller(unsigned int X, unsigned int Y)
{
  if(X >= m_ImageSize.x || Y >= m_ImageSize.y)
    return;
  if(getPixelStatus( X, Y) > 0)
    return;
  if(m_Image.getPixel( X, Y) == m_Color)
  {
    setPixelStatus( X, Y, 2);
    pipFiller( X + 1, Y);
    pipFiller( X, Y + 1);
    pipFiller( X - 1, Y);
    pipFiller( X, Y - 1);
  }

  return;
}

/**
 * DiceReader::getPixelStatus
 *
 * Gets the status value of the pixel at (x,y)
 *
 * @param X The x value for the pixel location
 * @param Y The y value for the pixel location
 * @return The status of the pixel;
 *  0 - untouched
 *  1 - touched normal pixel
 *  2 - touched pip pixel
 */

unsigned char DiceReader::getPixelStatus(unsigned int X, unsigned int Y)
{
  assert(X < m_ImageSize.x && Y < m_ImageSize.y);
  return m_PixelStatus[X][Y];
}

/**
 * DiceReader::setPixelStatus
 *
 * Sets the status of the pixle at (x,y). Throws an assertion
 * if the value snt is not in its range.
 *
 * @param X The x value for the pixel location
 * @param Y The y value for the pixel location
 * @param The status of the pixel;
 *  0 - untouched
 *  1 - touched normal pixel
 *  2 - touched pip pixel
 */

void DiceReader::setPixelStatus(unsigned int X, unsigned int Y, unsigned char status)
{
  assert( status <= 2);//check to see if it is in range
  assert(X < m_ImageSize.x && Y < m_ImageSize.y);
  m_PixelStatus[X][Y] = status;
}

/**
 * DiceReader::clearPixelStatus
 *
 * Sets m_PixelStatus contents to the value of 0.
 */

void DiceReader::clearPixelStatus()
{
  for(vector<vector<unsigned char> >::iterator it = m_PixelStatus.begin();
      it != m_PixelStatus.end(); it++)
  {
    fill(it->begin(), it->end(), 0);
  }
}
