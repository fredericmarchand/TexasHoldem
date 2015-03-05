#include "Dealer.h"

Dealer::Dealer()
{
    deckPointer = 0;

    int index = 0;
    int suit = HEARTS;
    for (; suit <= DIAMONDS; ++suit)
    {
        int value = TWO;
        for (; value <= ACE; ++value)
        {
            Card *card = new Card((Suit)suit, (CardValue)value);
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
            players[i]->addCardToHand(deck[deckPointer++], j);
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
