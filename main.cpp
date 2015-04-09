/*
 * TexasHoldemAI.cilk
 * 
 * Frederic Marchand
 * 100817579
 */

#include <cilk/cilk.h>
#include <cilktools/cilkview.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string.h>
using namespace std;

#include "Game.h"
#include "Player.h"

#define DEBUG 0 

int main(int argc, char** argv) 
{
	cout << "Starting new game" << endl;

	Game *game = new Game(2);
	Player *me = game->getPlayers()[0];
	Dealer *dealer = game->getDealer();
	dealer->shuffleDeck();
	dealer->distributeCards(game->getPlayers(), game->getPlayerCount());
	me->printHand();


    return 0;
}


