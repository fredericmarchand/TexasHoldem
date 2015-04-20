#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Card.h"

#define TOTAL_CARDS 52
#define SPLIT -1

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
    void flipFlop(bool verbose);
    void flipTurn(bool verbose);
    void flipRiver(bool verbose);
    void distributeCards();
    void shuffleDeck(int start); 
    Card* flipNextCard();
    void discardNextCard();
    int determineWinner();
    void printPot();
    bool playRound(Player *me, bool firstRound);
    void clearPlayerStates();
    void setPlayerStates();
    void addBetsToPot();
    bool checkLastPlayerRemaining(Player *player);
    void splitPot();
    void givePotToWinner(Player *winner);
    Move getMove();
    Card** getFlop();
    Card* getTurn();
    Card* getRiver();
    void swap(Card **a, Card **b);
    Card* getCard(Card *card);
    void setupAIGame(Player *player);
    void aiSwap(Player *player, bool fl, bool tu, bool ri);

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
