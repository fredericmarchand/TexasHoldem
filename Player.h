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
    Player(int chips);
    ~Player();
    void newHand(Card **newCards);
    int getChipCount();
    void setDealer(bool deal);

private:
    Card *hand[2];
    int chips;
    bool isDealer;
}

#endif //PLAYER_H
