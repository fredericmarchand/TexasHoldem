#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"

typedef enum moves {
    FOLD,
    CHECK,
    BET,
} Move;

class Player
{
public:
    Player();
    Player(int chips);
    ~Player();
    void addCardToHand(Card *newCard, int i);
    int getChipCount();
    void setDealer(bool deal);
    void printHand();

private:
    Card *hand[2];
    int chips;
    bool isDealer;
};

#endif //PLAYER_H
