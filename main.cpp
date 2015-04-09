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
#include <string>
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
	string move = "";

	cout << "Check (c), Bet (b), Fold (f)" << endl;
	cin >> move;
	if (move.compare("c") == 0)
	{

	}
	if (move.compare("b") == 0)
	{

	}
	if (move.compare("f") == 0)
	{

	}

	//Flop
	game->flipFlop();

	//Move
	cout << "Check (c), Bet (b), Fold (f)" << endl;
	cin >> move;
	if (move.compare("c") == 0)
	{

	}
	if (move.compare("b") == 0)
	{

	}
	if (move.compare("f") == 0)
	{

	}

	//Turn
	game->flipTurn();

	//Move
	cout << "Check (c), Bet (b), Fold (f)" << endl;
	cin >> move;
	if (move.compare("c") == 0)
	{

	}
	if (move.compare("b") == 0)
	{

	}
	if (move.compare("f") == 0)
	{

	}

	//River
	game->flipRiver();

	//Move
	cout << "Check (c), Bet (b), Fold (f)" << endl;
	cin >> move;
	if (move.compare("c") == 0)
	{

	}
	if (move.compare("b") == 0)
	{

	}
	if (move.compare("f") == 0)
	{

	}

	//Check Results

    return 0;
}


