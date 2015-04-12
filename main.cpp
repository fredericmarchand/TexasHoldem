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

Move doMove() 
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
    bool AI_game = true;
    Game *game = new Game(2);
    Player *me = game->getPlayers()[0];
    me->setDealer(true);

    if (argc > 1)
    {
        AI_game = false;
        me->setAI(false);
    }

    while (1)
    {
        //Check if the game is over
        if (game->getPlayers()[0]->getChipCount() == 0 || game->getPlayers()[1]->getChipCount() == 0)
        {
            break;
        }

        game->resetDeck();
        game->rotateDealerChip();

        printLabel("Starting new game");
        cout << "Small Blind: $" << SMALL_BLIND << endl;
        cout << "Big Blind:   $" << BIG_BLIND << endl;
        game->shuffleDeck();

        //Blinds
        game->getSmallBlindPlayer()->bet(SMALL_BLIND);
        game->getBigBlindPlayer()->bet(BIG_BLIND);

        game->distributeCards();
        me->printHand();

        /*Player *turn = game->getNextPlayer(game->getBigBlindPlayer());
        while (turn != game->getBigBlindPlayer())
        {
            if (PLAYERS_TURN)
            {
                doMove();
            }
            else //AI
            {
                //Call
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
            doMove();
        }
        else //AI
        {
            //Check
        }*/
            
        game->printPot();
        
        //Flop
        printLabel("Flop");
        game->flipFlop();

        //Round of betting

        game->printPot();

        //Turn
        printLabel("Turn");
        game->flipTurn();

        //Round of betting

        game->printPot();

        //River
        printLabel("River");
        game->flipRiver();

        //Final round of betting

        game->printPot();

        //Check Results and give pot to winner
        cout << endl;
        game->determineWinner();
        cin.ignore();
    }

    //Print winner
    cout << "The winner is: " << (game->getPlayers()[0]->getChipCount() == 0 ? "Player 2" : "Player 1") << endl;

    delete game;

    return 0;
}
