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
        cout << "Check/Call (c), Bet/Raise (b), Fold (f)" << endl;
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
        game->clearPlayerStates();
        game->rotateDealerChip();

        printLabel("Starting new game");
        cout << "Small Blind: $" << SMALL_BLIND << endl;
        cout << "Big Blind:   $" << BIG_BLIND << endl;
        cout << "Dealer: Player " << game->getPlayerIndex(game->getDealer()) << endl;
        game->shuffleDeck();

        //Blinds
        game->getSmallBlindPlayer()->bet(SMALL_BLIND);
        game->getBigBlindPlayer()->bet(BIG_BLIND);

        game->distributeCards();
        me->printHand();

        if (game->playRound(me, true) == true)
            goto end;

        //Finish blinds round
        game->printPot();
        
        //Flop
        printLabel("Flop");
        game->flipFlop();

        //Round of betting
        if (game->playRound(me, false))
            goto end;

        game->printPot();

        //Turn
        printLabel("Turn");
        game->flipTurn();

        //Round of betting
        if (game->playRound(me, false))
            goto end;

        game->printPot();

        //River
        printLabel("River");
        game->flipRiver();

        //Final round of betting
        game->playRound(me, false);

        game->printPot();

end:
        //Check Results and give pot to winner
        cout << endl;
        game->determineWinner();
        cin.ignore();
    }

    //Print winner
    cout << "The winner is: " << (game->getPlayers()[0]->getChipCount() == 0 ? "Player 1" : "Player 0") << endl;

    delete game;

    return 0;
}
