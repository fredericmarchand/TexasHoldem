/*
 * Texas Holdem AI
 * 
 * Frederic Marchand
 */

#include <iostream>
#include <string>
using namespace std;

#include "Game.h"
#include "Player.h"

#define DEBUG 0
#define VERBOSE true

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
        game->shuffleDeck(false);

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
        game->flipFlop(VERBOSE);

        //Round of betting
        if (game->playRound(me, false))
            goto end;

        game->printPot();

        //Turn
        printLabel("Turn");
        game->flipTurn(VERBOSE);

        //Round of betting
        if (game->playRound(me, false))
            goto end;

        game->printPot();

        //River
        printLabel("River");
        game->flipRiver(VERBOSE);

        //Final round of betting
        game->playRound(me, false);

        game->printPot();

end:
        //Check Results and give pot to winner
        cout << endl;
        int winnerIndex = game->determineWinner();
        if (winnerIndex == 0)
        {
            game->getPlayers()[0]->incHandsWon();
        }
        else if (winnerIndex == 1)
        {
            game->getPlayers()[1]->incHandsWon();
        }

        for (int i = 0; i < game->getPlayerCount(); ++i)
        {
            cout << "Player " << i << " has won " << game->getPlayers()[i]->getHandsWon() << " games" << endl;
        }
        
        cin.ignore();
        //break;
    }

    //Print winner
    cout << "The winner is: " << (game->getPlayers()[0]->getChipCount() == 0 ? "Player 1" : "Player 0") << endl;

    delete game;

    return 0;
}
