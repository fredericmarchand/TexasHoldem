#include "Game.h"
#include <cstdlib>
#include <iostream>
#include "Search.h"
#include "CardUtil.h"

using namespace std;

Game::Game(int numPlayers)
{
    this->numPlayers = numPlayers;
    players = new Player*[numPlayers];
    for (int i = 0; i < numPlayers; ++i)
    {
        players[i] = new Player(1000, true);
    }

    deckPointer = 0;

    int index = 0;
    int suit = HEARTS;
    for (; suit <= DIAMONDS; ++suit)
    {
        int value = TWO;
        for (; value <= ACE; ++value)
        {
            Card *card = new Card((Suit)suit, (CardValue)value);
            deck[index++] = card;
        }
    }
}

Game::Game(Game *game)
{
    numPlayers = game->getPlayerCount();
    players = new Player*[numPlayers];
    for (int i = 0; i < numPlayers; ++i)
    {
        players[i] = new Player(game->getPlayers()[i]);
    }
    
    deckPointer = game->deckPointer;

    for (int i = 0; i < TOTAL_CARDS; ++i)
    {
        Card *card = new Card(game->deck[i]);
        deck[i] = card;
    }
}

Game::~Game()
{
    for (int i = 0; i < numPlayers; ++i)
    {
        delete players[i];
    }
    delete [] players;

    for (int i = 0; i < TOTAL_CARDS; ++i)
    {
        delete deck[i];
    }
}

void Game::resetDeck()
{
    deckPointer = 0;
}

Player** Game::getPlayers()
{
    return players;
}

int Game::getPlayerCount()
{
    return numPlayers;
}

int Game::getPot()
{
    return pot;
}

void Game::rotateDealerChip()
{
    int dealer;
    for (int i = 0; i < numPlayers; ++i)
    {
        if (players[i]->isDealer())
        {
           dealer = i;
           break;
        }
    }
    players[dealer]->setDealer(false);
    if (dealer == 0)
    {
        players[numPlayers-1]->setDealer(true);
    }
    else
    {
        players[dealer-1]->setDealer(true);
    }
}

Player* Game::getDealer()
{
    for (int i = 0; i < numPlayers; ++i)
    {
        if (players[i]->isDealer())
        {
           return players[i];
        }
    }
}

Player* Game::getBigBlindPlayer()
{
    int dealer;
    for (int i = 0; i < numPlayers; ++i)
    {
        if (players[i]->isDealer())
        {
           dealer = i;
           break;
        }
    }
    if (dealer == 0) 
    {
        return players[numPlayers-2];
    }
    
    if (numPlayers == 2)
    {
        return players[dealer];
    }
    return players[dealer-2];
}

Player* Game::getSmallBlindPlayer()
{
    int dealer;
    for (int i = 0; i < numPlayers; ++i)
    {
        if (players[i]->isDealer())
        {
           dealer = i;
           break;
        }
    }
    if (dealer == 0) 
    {
        return players[numPlayers-1];
    }
    return players[dealer-1];
}

Player* Game::getNextPlayer(Player *player)
{
    int index = 0;
    for (int i = 0; i < numPlayers; ++i)
    {
        if (player == players[i])
        {
            index = i;
            break;
        }
    }
    if (index == 0)
    {
        return players[numPlayers-1];
    }
    return players[index-1];
}

Player* Game::getPreviousPlayer(Player *player)
{
    int index = 0;
    for (int i = 0; i < numPlayers; ++i)
    {
        if (player == players[i])
        {
            index = i;
            break;
        }
    }

    do {
        index++;
        if (index == numPlayers)
        {
            index = 0;
        }
    }
    while (players[index]->getState().move == FOLD);

    return players[index];
}

int Game::getPlayerIndex(Player *player)
{
    for (int i = 0; i < numPlayers; ++i)
    {
        if (player == players[i])
        {
            return i;
        }
    }
}

void Game::flipFlop()
{
    discardNextCard();
    flop[0] = flipNextCard();
    flop[1] = flipNextCard();
    flop[2] = flipNextCard();
    printCardArray(flop, 3);
}

void Game::flipTurn()
{
    discardNextCard();
    turn = flipNextCard();
    turn->printCard();
}

void Game::flipRiver()
{
    discardNextCard();
    river = flipNextCard();
    river->printCard();
}

void Game::distributeCards() 
{
    for (int j = 0; j < 2; ++j)
    {
        for (int i = 0; i < numPlayers; ++i)
        {
            players[i]->addCardToHand(deck[deckPointer++], j);
        }
    }
}

void swap(Card **a, Card **b)
{
    Card *temp = *a;
    *a = *b;
    *b = temp;
}

void Game::shuffleDeck()
{
    // Use a different seed value so that we don't get same
    // result each time we run this program
    srand ( time(NULL) );
 
    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = TOTAL_CARDS-1; i >= 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i+1);
 
        // Swap arr[i] with the element at random index
        swap(&deck[i], &deck[j]);
    }
}

Card* Game::flipNextCard()
{
    Card *card = deck[deckPointer];
    deckPointer++;
    return card; 
}

void Game::discardNextCard()
{
    deckPointer++;
}

//Needs to be more in depth
Player* Game::determineWinner()
{
    //Check if everyone folded but one person
    for (int i = 0; i < numPlayers; ++i)
    {
        if (checkLastPlayerRemaining(players[i]) == true)
        {
            givePotToWinner(players[i]);
            return players[i];
        }
    }

    Hand hands[numPlayers];
    Hand best = NOTHING;
    int playerIndex;
    for (int i = 0; i < numPlayers; ++i) {
        hands[i] = players[i]->bestHand(flop, turn, river);

        if (hands[i] > best)
        {
            best = hands[i];
            playerIndex = i;
        }
        cout << "Hand: " << hands[i] << endl;
        cout << endl;
    }

    givePotToWinner(players[playerIndex]);

    return players[playerIndex];
}

void Game::givePotToWinner(Player *winner)
{
    winner->addChips(pot);
    cout << "Winner: Player " << getPlayerIndex(winner) << endl;
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Player " << i << ": $" << players[i]->getChipCount() << endl;
    }
    pot = 0;
}

void Game::printPot()
{
    cout << endl;
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Player " << i << ": $" << players[i]->getChipCount() << endl;
    }
    cout << "Pot: $" << pot << endl;
    cin.ignore();
}

bool Game::playRound(Player *me, bool firstRound)
{
    Player *last = NULL;
    Player *turn = NULL;

    //If its the first round, the players turn is the player after the big blind
    if (firstRound)
    {
        turn = getNextPlayer(getBigBlindPlayer());
        last = getBigBlindPlayer();
    }
    else //Otherwise its the small blind player who goes first
    {
        turn = getSmallBlindPlayer();
        last = getDealer();
    }

    while (1)
    {
        if (checkLastPlayerRemaining(turn) == true)
        {
            break;
        }

        if (turn->getState().move == FOLD)
        {
            turn = getNextPlayer(turn);
            continue;
        }

        Move move = CHECK;
        if (turn == me && !me->isAI())
        {
            Move move = getMove();
            me->doMove(move);
        }
        else
        {
            move = turn->doMove(getPlayerIndex(turn), getPreviousPlayer(turn));
        }

        // Change last player to make a move
        if (move == BET)
        {
            last = getPreviousPlayer(turn);
        }

        // Exit condition
        if (turn == last)
        {
            break;
        }

        turn = getNextPlayer(turn);
    }

    addBetsToPot();
    setPlayerStates();

    for (int i = 0; i < numPlayers; ++i)
    {
        if (checkLastPlayerRemaining(players[i]) == true)
        {
            return true;
        }
    }

    return false;
}

void Game::setPlayerStates()
{
    for (int i = 0; i < numPlayers; ++i)
    {
        if (players[i]->getState().move != FOLD)
        {
            players[i]->setState(CHECK, 0);
        }
    }
}

void Game::clearPlayerStates()
{
    for (int i = 0; i < numPlayers; ++i)
    {
        players[i]->setState(CHECK, 0);
    }
}

void Game::addBetsToPot()
{
    for (int i = 0; i < numPlayers; ++i)
    {
        pot += players[i]->getState().bet;
        //players[i]->setState(players[i]->getState().move, 0);
    }
}

bool Game::checkLastPlayerRemaining(Player *player)
{
    bool ret = true;
    if (player->getState().move == FOLD)
        return false;

    for (int i = 0; i < numPlayers; ++i)
    {
        if (players[i] != player)
        {
            ret &= (players[i]->getState().move == FOLD);
        }
    }
    return ret;
}

Move Game::getMove()
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
