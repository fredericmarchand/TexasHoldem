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

Move aiMove(Game *game) 
{
    return CHECK;
}

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
    me->setDealer(true);

    while (1)
    {
        if (game->getPlayers()[0]->getChipCount() == 0 || game->getPlayers()[1]->getChipCount() == 0)
        {
            break;
        }

        game->resetDeck();
        game->rotateDealerChip();

        cout << "=================" << endl;
        cout << "Starting new game" << endl;
        cout << "=================" << endl;
        game->shuffleDeck();

        //blinds
        game->getSmallBlindPlayer()->bet(game->getPot(), SMALL_BLIND);
        game->getBigBlindPlayer()->bet(game->getPot(), BIG_BLIND);
        cout << "Pot: $" << *(game->getPot()) << endl;

        game->distributeCards();
        me->printHand();

        Player *turn = game->getNextPlayer(game->getBigBlindPlayer());
        while (turn != game->getBigBlindPlayer())
        {
            //if (turn == me)
            //{
                //Do actual move
            //}
            //else
            //{
                //Perform AI move
                if (turn == game->getSmallBlindPlayer())
                {
                    turn->bet(game->getPot(), SMALL_BLIND);
                }
                else
                {
                    turn->bet(game->getPot(), BIG_BLIND);
                }
            //}

            turn = game->getNextPlayer(turn);
        }
        //Perform big blind players move
            //Check for now
        cout << "Pot: $" << *(game->getPot()) << endl;
        cin.ignore();

        //Check for now
        //Move move;

        /*move = doMove(game);
        if (move == FOLD) 
        {
            continue;
        }
        else if (move == CHECK)
        {

        }
        else if (move == BET)
        {

        }
        else
        {
            
        }*/

        //Flop
        cout << "====" << endl;
        cout << "Flop" << endl;
        cout << "====" << endl;
        game->flipFlop();
        cin.ignore();

        //Moves
        /*move = doMove(game);
        if (move == FOLD) 
        {
            continue;
        }
        else if (move == CHECK)
        {

        }
        else if (move == BET)
        {

        }
        else
        {

        }*/

        //Turn
        cout << "====" << endl;
        cout << "Turn" << endl;
        cout << "====" << endl;
        game->flipTurn();
        cin.ignore();

        //Check for now
        //Moves
        /*move = doMove(game);
        if (move == FOLD) 
        {
            continue;
        }
        else if (move == CHECK)
        {

        }
        else if (move == BET)
        {

        }
        else
        {
            
        }*/

        //River
        cout << "=====" << endl;
        cout << "River" << endl;
        cout << "=====" << endl;
        game->flipRiver();
        cin.ignore();

        //Check for now
        //Moves
        /*move = doMove(game);
        if (move == FOLD) 
        {
            continue;
        }
        else if (move == CHECK)
        {

        }
        else if (move == BET)
        {

        }
        else
        {
            
        }*/

        //Check Results
        //Give Pot to winner
        cout << endl;
        game->determineWinner();
        cin.ignore();

    }

    cout << "The winner is: " << (game->getPlayers()[0]->getChipCount() == 0 ? "Player 2" : "Player 1") << endl;


    return 0;
}
