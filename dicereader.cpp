#include"dicereader.h"

/**
 *
 * DiceReader::DiceReader
 *
 * Constructor for DiceReader
 */

DiceReader::DiceReader()
{
  diceTotal = 0;
}

/**
 *
 * DiceReader::diceCount
 *
 * Parses through an image to gind the number represented on a dice
 *
 * @param imageName The name of the image to process
 * @return The unsigned int value represented by the dice
 */

unsigned int DiceReader::diceCount(string imageName)
{
  if(imageName != " ")
    return 1;
  return 0;
}

/**
 *
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
