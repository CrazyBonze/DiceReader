#include"dicereader.h"

const double DiceReader::PERCENT_DIF = .08;

/**
 * DiceReader::DiceReader
 *
 * Constructor for DiceReader
 */

DiceReader::DiceReader()
{
  //this will be the color of the pip, black for testing
  m_Color = sf::Color(15,15,15,255);
  m_DiceTotal = 0;//set to 0 because we have not counted anything
  //reserve this image size, this will be the default size for ease of use
  m_X = 640;
  m_Y = 400;
  resizePixelStatus( m_X, m_Y);
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

  if(m_ImageSize. x > m_X || m_ImageSize.y > m_Y)
    resizePixelStatus( m_ImageSize.x, m_ImageSize.y);

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

  //i will have to search for a place to start but for now this place will do
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
      if(int(*it2) == 1)
        cout << ' ';
      else
        cout << int(*it2);
    }
    cout << endl;
  }
}

/**
 * DiceReader::resizePixelStatus
 *
 * Resizes the 2d vector matrix that contains the status of the pixels
 *
 * @param X The x value of the matrix
 * @param Y The y value of the matrix
 */

void DiceReader::resizePixelStatus(unsigned int X, unsigned int Y)
{
  m_PixelStatus.resize( X, vector<unsigned char>( Y, 0));//fill status with 0
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
  if( X >= m_ImageSize.x || Y >= m_ImageSize.y)
    return;
  if( getPixelStatus( X, Y) > 0)
    return;
  sf::Color sample = m_Image.getPixel( X, Y);
  if( !pixelCompare( sample, m_Color, PERCENT_DIF))
  {
    setPixelStatus( X, Y, 1);
  }
  else
  {
    m_DiceTotal++;
    pipFiller( X, Y);
  }

  floodFind( X + 1, Y);
  floodFind( X, Y + 1);
  floodFind( X - 1, Y);
  floodFind( X, Y - 1);

  return;
}

/**
 * DiceReader::pixelCompare
 *
 * Compares two pixels based on r, g, and b values independently,
 * if one or more is not in the range than it returns false.
 *
 * @param sample The color of the pixel that is being processed
 * @param master The color of the pixel to compare sample to
 * @param percent The percentage of how close sample should be to master
 *
 * @return if r, g, and b of sample are all within +- percent of master
 */

bool DiceReader::pixelCompare(sf::Color sample, sf::Color master, double percent)
{
  double range = 255 * percent;
  double masterAvg = (master.r + master.g + master.b) / 3;
  double sampleAvg = (sample.r + sample.g + sample.b) / 3;

  return range >= abs(masterAvg - sampleAvg);
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
  //if(m_Image.getPixel( X, Y) == m_Color)
  sf::Color sample = m_Image.getPixel( X, Y);
  if( pixelCompare( sample, m_Color, PERCENT_DIF))
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
