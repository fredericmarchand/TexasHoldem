#include "Card.h"

#include <iostream>
using namespace std;

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

string Card::getSuitSymbol()
{
    switch (suit)
    {
    case HEARTS:
        return "♥";
    case SPADES:
        return "♠";
    case CLUBS:
        return "♣";
    case DIAMONDS:
        return "♣";
    }
}

string Card::getValueSymbol()
{
    switch (value)
    {
    case TWO:
        return " 2";
    case THREE:
        return " 3";
    case FOUR:
        return " 4";
    case FIVE:
        return " 5";
    case SIX:
        return " 6";
    case SEVEN:
        return " 7";
    case EIGHT:
        return " 8";
    case NINE:
        return " 9";
    case TEN:
        return "10";
    case JACK:
        return " J";
    case QUEEN:
        return " Q";
    case KING:
        return " K";
    case ACE:
        return " A";
    }
}

void Card::printCard()
{
    cout << "|----------|" << endl;
    cout << "|          |" << endl;
    cout << "|          |" << endl;
    cout << "|   " << getValueSymbol() << getSuitSymbol() << "    |" << endl;
    cout << "|          |" << endl;
    cout << "|          |" << endl;
    cout << "|----------|" << endl;
}
