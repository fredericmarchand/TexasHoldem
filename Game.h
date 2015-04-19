#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Card.h"

#define TOTAL_CARDS 52

class Game
{
public:
    Game(int numPlayers);
    Game(Game *game);
    ~Game();
    void resetDeck();
    Player** getPlayers();
    int getPlayerCount();
    int getPot();
    void rotateDealerChip();
    Player* getDealer();
    Player* getBigBlindPlayer();
    Player* getSmallBlindPlayer();
    Player* getNextPlayer(Player *player);
    Player* getPreviousPlayer(Player *player);
    int getPlayerIndex(Player *player);
    void movePlayersCardsToBack();
    void flipFlop();
    void flipTurn();
    void flipRiver();
    void distributeCards();
    void shuffleDeck(); 
    Card* flipNextCard();
    void discardNextCard();
    Player* determineWinner();
    void printPot();
    bool playRound(Player *me, bool firstRound);
    void clearPlayerStates();
    void setPlayerStates();
    void addBetsToPot();
    bool checkLastPlayerRemaining(Player *player);
    void givePotToWinner(Player *winner);
    Move getMove();

private:
    Player **players;
    int numPlayers;
    int pot;
    Card *flop[3];
    Card *turn;
    Card *river;
    int deckPointer;
    Card *deck[TOTAL_CARDS];
};

#endif //GAME_H
