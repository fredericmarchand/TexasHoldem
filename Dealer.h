#ifndef DEALER_H
#define DEALER_H

#include "Player.h"
#include "Card.h"

class Dealer
{
public:
    Dealer();
    ~Dealer();
    void distributeCards(Player **players, int numPlayers);
    void shuffleDeck(); 
    Card* flipNextCard();
    void discardNextCard();
private:
    int deckPointer;
    Card *deck[52];
};

#endif //DEALER_H
