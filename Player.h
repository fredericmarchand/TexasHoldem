#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"

typedef enum moves {
    FOLD,
    CHECK,
    BET,
    CALL,
} Move;

class Player
{
public:
    Player();
    Player(int chips);
    ~Player();
    void addCardToHand(Card *newCard, int i);
    int getChipCount();
    bool isDealer();
    void setDealer(bool deal);
    void printHand();
    bool bet(int *pot, int value);

private:
    Card *hand[2];
    int chips;
    bool dealer;
};

#endif //PLAYER_H
