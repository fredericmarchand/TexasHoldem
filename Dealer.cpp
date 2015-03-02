#include "Dealer.h"

Dealer::Dealer()
{
    deckPointer = 0;

    int index = 0;
    Suit suit = HEARTS;
    for (; suit <= DIAMONDS; ++suit)
    {
        CardValue value = TWO;
        for (; value <= ACE; ++value)
        {
            Card *card = new Card(suit, value);
            deck[index++] = card;
        }
    }
}

Dealer::~Dealer()
{
    for (int i = 0; i < 52; ++i)
    {
        delete deck[i];
    }
}

void Dealer::distributeCards(Player **players, int numPlayers) 
{
    for (int j = 0; j < 2; ++j)
    {
        for (int i = 0; i < numPlayers; ++i)
        {
            players[i]->newHand(deck[deckPointer++]);
        }
    }
}

void Dealer::shuffleDeck()
{
}

Card* Dealer::flipNextCard()
{
        Card *card = deck[deckPointer];
        deckPointer++;
        return card; 
}

void Dealer::discardNextCard()
{
        deckPointer++;
}
