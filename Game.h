#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Card.h"

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
    Player* getPreviousPlayer(Player *player);
    int getPlayerIndex(Player *player);
    void flipFlop();
    void flipTurn();
    void flipRiver();
    void distributeCards();
    void shuffleDeck(); 
    Card* flipNextCard();
    void discardNextCard();
    Player* determineWinner();
    void printPot();
    void playRound(Player *me, bool firstRound);
    void clearPlayerStates();
    void addBetsToPot();

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
