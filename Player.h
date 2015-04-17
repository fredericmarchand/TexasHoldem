#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "CardUtil.h"

#define SMALL_BLIND     50
#define BIG_BLIND       100
#define DEFAULT_BET     BIG_BLIND

typedef enum moves {
    FOLD,
    CHECK,  // CHECK / CALL
    BET,    // BET / RAISE
} Move;

typedef struct playerState {
    Move move;
    int bet;
} State;

class Player
{
public:
    Player();
    Player(int chips, bool ai);
    Player(Player *player);
    ~Player();
    void addCardToHand(Card *newCard, int i);
    int getChipCount();
    int addChips(int pot);
    int removeChips(int amount);
    bool isDealer();
    bool isAI();
    void setAI(bool ai);
    void setDealer(bool deal);
    void printHand();
    State getState();
    void setState(Move move, int bet);
    bool bet(int value);
    void check();
    void fold();
    Hand bestHand(Card** flop, Card *turn, Card *river);
    Move doMove(int index, Player *last);
    Move doMove(Move move);

private:
    Card *hand[2];
    int chips;
    bool dealer;
    State state;
    bool ai;
};

#endif //PLAYER_H
