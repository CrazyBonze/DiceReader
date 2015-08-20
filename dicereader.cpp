#include"dicereader.h"

const double DiceReader::PERCENT_DIF = .10;

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

  m_PixelState = new Matrix( m_X, m_Y);
  m_PixelState->fill(0);
}

/**
 * DiceReader::~DiceReader
 *
 * Destructor for DiceReader, deletes the pixele state matrix
 */

DiceReader::~DiceReader()
{
  delete m_PixelState;
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
  m_PixelState->fill(0);
  m_DiceTotal = 0;
  if(!m_Image.loadFromFile(imageName))
  {
    cerr << "ERROR: Could not load image from disk!" << endl;
    return m_DiceTotal;
  }

  m_ImageSize = m_Image.getSize();
  resizePixelStatus( m_ImageSize.x, m_ImageSize.y);

  //i will have to search for a place to start but for 
  //now this place will do
  floodFind( 1, 1);

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
  for(unsigned int i = 0; i < m_X; i+=scale)
  {
    for(unsigned int j = 0; j < m_Y; j+=scale)
    {
      if(int(m_PixelState->get(i,j)) == 1)
        cout << ' ';
      else
        cout << int(m_PixelState->get(i,j));
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
  //resize and fill with 0
  if( X != m_X || Y != m_Y)
  {
    delete m_PixelState;
    m_X = X;
    m_Y = Y;
    m_PixelState = new Matrix( m_X, m_Y);
  }
  m_PixelState->fill(0);
}

/**
 * DiceReader::floodFind
 *
 * Recursive flood fill modified to find the pips on one of the six 
 * sides of a common dice. It marks each pixel as read until it find one of
 * the darker pixels representing the pips of a die. When it finds a pip 
 * pixel it passes to pipFiller to mark tose pixels as read and ads one to 
 * diceTotal.
 */

void DiceReader::floodFind(unsigned int X, unsigned int Y)
{
  if( X >= m_ImageSize.x || Y >= m_ImageSize.y)
    return;
  if( m_PixelState->get( X, Y) > 0)
    return;
  sf::Color sample = m_Image.getPixel( X, Y);
  if( !pixelCompare( sample, m_Color, PERCENT_DIF))
  {
    m_PixelState->set( X, Y, 1);
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

bool DiceReader::pixelCompare(sf::Color sample, sf::Color master, 
    double percent)
{
  double range = 255 * percent;
  double masterAvg = (master.r + master.g + master.b) / 3;
  double sampleAvg = (sample.r + sample.g + sample.b) / 3;

  //return range >= abs(masterAvg - sampleAvg);
  double total = masterAvg - sampleAvg;
  if(total < 0)
    total *= -1;
  return range >= total;
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
  if( m_PixelState->get( X, Y) > 0)
    return;
  //if(m_Image.getPixel( X, Y) == m_Color)
  sf::Color sample = m_Image.getPixel( X, Y);
  if( pixelCompare( sample, m_Color, PERCENT_DIF))
  {
    m_PixelState->set( X, Y, 2);
    pipFiller( X + 1, Y);
    pipFiller( X, Y + 1);
    pipFiller( X - 1, Y);
    pipFiller( X, Y - 1);
  }

  return;
}
