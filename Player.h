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
    Player(int chips, bool ai);
    ~Player();
    void addCardToHand(Card *newCard, int i);
    int getChipCount();
    int addChips(int pot);
    bool isDealer();
    bool isAI();
    void setDealer(bool deal);
    void printHand();
    Move getState();
    void setState(Move move);
    bool bet(int *pot, int value);
    Hand bestHand(Card** flop, Card *turn, Card *river);

private:
    Card *hand[2];
    int chips;
    bool dealer;
    Move state;
    bool ai;
};

#endif //PLAYER_H
