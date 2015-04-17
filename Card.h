#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

typedef enum suits {
    HEARTS      = 0,
    SPADES      = 1,
    CLUBS       = 2,
    DIAMONDS    = 3,
} Suit;

typedef enum card_values {
    TWO     = 2,
    THREE   = 3,
    FOUR    = 4,
    FIVE    = 5,
    SIX     = 6,
    SEVEN   = 7,
    EIGHT   = 8,
    NINE    = 9,
    TEN     = 10,
    JACK    = 11,
    QUEEN   = 12,
    KING    = 13,
    ACE     = 14,
} CardValue;

class Card 
{
public:
    Card(Suit suit, CardValue value);
    Card(Card *card);
    ~Card();
    Suit getSuit();
    CardValue getCardValue();
    string getSuitSymbol();
    string getValueSymbol();
    void printCard();

private:
    Suit suit;
    CardValue value;
};

#endif //CARD_H
