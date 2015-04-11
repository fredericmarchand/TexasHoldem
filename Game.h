#ifndef GAME_H
#define GAME_H

#include "Player.h"
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
    int getPlayerCount();
    void rotateDealerChip();
    void flipFlop();
    void flipTurn();
    void flipRiver();
    void distributeCards();
    void shuffleDeck(); 
    Card* flipNextCard();
    void discardNextCard();
    static int evaluateHand(Card *hand[]);
    static int compareCards(const void *card1, const void *card2);

private:
    Player **players;
    int numPlayers;
    int pot;
    Card *flop[3];
    Card *turn;
    Card *river;
    int deckPointer;
    Card *deck[52];
};

#endif //GAME_H
