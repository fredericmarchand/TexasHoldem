#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Dealer.h"
#include "Card.h"

class Game
{
public:
    Game(int numPlayers);
    ~Game();
    Player** getPlayers();
    Dealer* getDealer();
    int getPlayerCount();
    void rotateDealerChip();

private:
    Player **players;
    Dealer dealer;
    int numPlayers;
    int pot
    Card *flop[3];
    Card *turn;
    Card *river;
}

#endif //GAME_H
