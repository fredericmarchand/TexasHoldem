#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "CardUtil.h"

typedef enum moves {
    FOLD,
    CHECK,
    BET,
    CALL,
    ALL_IN,
} Move;

class Player
{
public:
    Player();
    Player(int chips);
    ~Player();
    void addCardToHand(Card *newCard, int i);
    int getChipCount();
    int addChips(int pot);
    bool isDealer();
    void setDealer(bool deal);
    void printHand();
    bool bet(int *pot, int value);
    Hand bestHand(Card** flop, Card *turn, Card *river);
    //void performMove(Game *game);

private:
    Card *hand[2];
    int chips;
    bool dealer;
    Move handState;
};

#endif //PLAYER_H
