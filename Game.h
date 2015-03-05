#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Dealer.h"
#include "Card.h"

typedef enum hands {
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH,
} Hand;

class Game
{
public:
    Game(int numPlayers);
    ~Game();
    Player** getPlayers();
    Dealer* getDealer();
    int getPlayerCount();
    void rotateDealerChip();
    static int evaluateHand(Card *hand[]);
    static int compareCards(const void *card1, const void *card2);

private:
    Player **players;
    Dealer dealer;
    int numPlayers;
    int pot;
    Card *flop[3];
    Card *turn;
    Card *river;
};

#endif //GAME_H
