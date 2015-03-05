#include "Card.h"

Card::Card(Suit suit, CardValue value)
{
    this->suit = suit;
    this->value = value;
}

Card::~Card()
{
}

Suit Card::getSuit()
{
    return suit;
}

CardValue Card::getCardValue()
{
    return value;
}
