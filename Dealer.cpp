#include "Dealer.h"
#include <time.h>
#include <cstdlib>
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

void swap (Card **a, Card **b)
{
    Card *temp = *a;
    *a = *b;
    *b = temp;
}

void Dealer::shuffleDeck()
{
    // Use a different seed value so that we don't get same
    // result each time we run this program
    srand ( time(NULL) );
 
    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = 52; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i+1);
 
        // Swap arr[i] with the element at random index
        swap(&deck[i], &deck[j]);
    }
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
