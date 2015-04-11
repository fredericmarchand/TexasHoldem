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
#define PLAYERS_TURN (turn == me && !AI_game)

Move aiMove(Game *game) 
{
    return CHECK;
}

void printLabel(string label)
{
    for (int i = 0; i < label.length(); ++i)
    {
        cout << "=";
    }
    cout << endl << label << endl;
    for (int i = 0; i < label.length(); ++i)
    {
        cout << "=";
    }
    cout << endl;
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
    bool AI_game = false;
    Game *game = new Game(2);
    Player *me = game->getPlayers()[0];
    me->setDealer(true);

    if (argc > 1)
        AI_game = true;

    while (1)
    {
        if (game->getPlayers()[0]->getChipCount() == 0 || game->getPlayers()[1]->getChipCount() == 0)
        {
            break;
        }

        game->resetDeck();
        game->rotateDealerChip();

        printLabel("Starting new game");
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
            if (PLAYERS_TURN)
            {
                doMove(game);
            }
            else //AI
            {
                if (turn == game->getSmallBlindPlayer())
                {
                    turn->bet(game->getPot(), SMALL_BLIND);
                }
                else
                {
                    turn->bet(game->getPot(), BIG_BLIND);
                }
            }

            turn = game->getNextPlayer(turn);
        }
        //Perform big blind players move
        if (PLAYERS_TURN)
        {
            //Check for now
            doMove(game);
        }
        else //AI
        {
            //Check
        }
            
        cout << "Pot: $" << *(game->getPot()) << endl;
        cin.ignore();
        
        //Flop
        printLabel("Flop");
        game->flipFlop();

        //Round of betting

        cout << "Pot: $" << *(game->getPot()) << endl;
        cin.ignore();

        //Turn
        printLabel("Turn");
        game->flipTurn();

        //Round of betting

        cout << "Pot: $" << *(game->getPot()) << endl;
        cin.ignore();

        //River
        printLabel("River");
        game->flipRiver();
        cout << "Pot: $" << *(game->getPot()) << endl;
        cin.ignore();

        //Final round of betting

        cout << "Pot: $" << *(game->getPot()) << endl;

        //Check Results and give pot to winner
        cout << endl;
        game->determineWinner();
        cin.ignore();
    }

    cout << "The winner is: " << (game->getPlayers()[0]->getChipCount() == 0 ? "Player 2" : "Player 1") << endl;

    return 0;
}
