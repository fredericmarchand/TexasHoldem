#include "Game.h"

Game::Game(int numPlayers)
{
        this.numPlayers = numPlayers;
        players = new Player[numPlayers];
        for (int i = 0; i < numPlayers; ++i)
        {
            players[i] = new Player(1000);
        }
}

Game::~Game()
{
        for (int i = 0; i < numPlayers; ++i)
        {
                delete players[i];
        }
        delete [] players;
}

