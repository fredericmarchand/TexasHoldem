/*
 * TexasHoldemAI.cilk
 * 
 * Frederic Marchand
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

Move doMove(Game *game) 
{
	Move move;
	string moveStr = "";

	while (moveStr.compare("c") != 0 && moveStr.compare("b") != 0 && moveStr.compare("f") != 0)
	{
		cout << "Check (c), Bet (b), Fold (f)" << endl;
		cin >> moveStr;
	}
	if (moveStr.compare("c") == 0)
	{
		move = CHECK;
	}
	if (moveStr.compare("b") == 0)
	{
		move = BET;
	}
	if (moveStr.compare("f") == 0)
	{
		move = FOLD;
	}

	return move;
}

int main(int argc, char** argv) 
{
	Game *game = new Game(2);
	Player *me = game->getPlayers()[0];

	while (1)
	{
		cout << "=================" << endl;
		cout << "Starting new game" << endl;
		cout << "=================" << endl;
		game->shuffleDeck();
		game->distributeCards();
		me->printHand();

		Move move;

		move = doMove(game);
		if (move == FOLD) 
		{
			continue;
		}

		//Flop
		cout << "====" << endl;
		cout << "Flop" << endl;
		cout << "====" << endl;
		game->flipFlop();

		//Move
		move = doMove(game);
		if (move == FOLD) 
		{
			continue;
		}

		//Turn
		cout << "====" << endl;
		cout << "Turn" << endl;
		cout << "====" << endl;
		game->flipTurn();

		//Move
		move = doMove(game);
		if (move == FOLD) 
		{
			continue;
		}

		//River
		cout << "=====" << endl;
		cout << "River" << endl;
		cout << "=====" << endl;
		game->flipRiver();

		//Move
		move = doMove(game);
		if (move == FOLD) 
		{
			continue;
		}

		//Check Results
	}

    return 0;
}
