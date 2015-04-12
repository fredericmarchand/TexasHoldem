#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Card.h"

#define SMALL_BLIND     50
#define BIG_BLIND       100
#define DEFAULT_BET     BIG_BLIND

class Game
{
public:
    Game(int numPlayers);
    ~Game();
    void resetDeck();
    Player** getPlayers();
    int getPlayerCount();
    int* getPot();
    void rotateDealerChip();
    Player* getDealer();
    Player* getBigBlindPlayer();
    Player* getSmallBlindPlayer();
    Player* getNextPlayer(Player *player);
    void flipFlop();
    void flipTurn();
    void flipRiver();
    void distributeCards();
    void shuffleDeck(); 
    Card* flipNextCard();
    void discardNextCard();
    Player* determineWinner();
    void printPot();

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
