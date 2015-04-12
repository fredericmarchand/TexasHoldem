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

Game::~Game()
{
    for (int i = 0; i < numPlayers; ++i)
    {
        delete players[i];
    }
    delete [] players;

    for (int i = 0; i < 52; ++i)
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

int* Game::getPot()
{
    return &pot;
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
    if (index == numPlayers-1)
    {
        return players[0];
    }
    return players[index+1];
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
    for (int i = 51; i >= 0; i--)
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
        cout << endl;
    }
    players[playerIndex]->addChips(pot);
    cout << "Winner: Player " << playerIndex << endl;
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Player " << i << ": $" << players[i]->getChipCount() << endl;
    }
    pot = 0;
    return players[playerIndex];
}

void Game::printPot()
{
    cout << "Pot: $" << pot << endl;
    cin.ignore();
}

void Game::playRound(Player *me, bool firstRound)
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

    while (turn != last)
    {
        if (turn->getState().move == FOLD)
        {
            turn = getNextPlayer(turn);
            continue;
        }

        Move move = CHECK;
        if (turn == me && !me->isAI())
        {
            move = me->doMove(move);
        }
        else
        {
            move = me->doMove(getPlayerIndex(turn), getPreviousPlayer(turn));
        }

        //handle move
        if (move == BET)
        {
            last = turn;
        }

        turn = getNextPlayer(turn);
    }

    Move move = CHECK;
    if (turn == me && !me->isAI())
    {
        move = me->doMove(move);
    }
    else
    {
        move = turn->doMove(getPlayerIndex(turn), getPreviousPlayer(turn));
    }

    //handle move

    addBetsToPot();
    clearPlayerStates();
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
    }
}
