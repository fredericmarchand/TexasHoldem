#include "Game.h"
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "Search.h"
#include "CardUtil.h"

using namespace std;

Game::Game(int numPlayers)
{
    this->numPlayers = numPlayers;
    players = new Player*[numPlayers];
    for (int i = 0; i < numPlayers; ++i)
    {
        players[i] = new Player(100000, true);
    }

    deckPointer = 0;

    int index = 0;
    int suit = HEARTS;
    for (; suit <= DIAMONDS; ++suit)
    {
        int value = TWO;
        for (; value <= ACE; ++value)
        {
            deck[index++] = new Card((Suit)suit, (CardValue)value);
        }
    }
    resetDeck();
}

Game::Game(Game *game)
{
    numPlayers = game->getPlayerCount();
    players = new Player*[numPlayers];
    for (int i = 0; i < numPlayers; ++i)
    {
        players[i] = new Player(game->getPlayers()[i]);
    }
    
    deckPointer = 0;

    for (int i = 0; i < TOTAL_CARDS; ++i)
    {
        deck[i] = new Card(game->deck[i]);
    }

    flop[0] = getCard(game->flop[0]);
    flop[1] = getCard(game->flop[1]);
    flop[2] = getCard(game->flop[2]);
    turn = getCard(game->turn);
    river = getCard(game->river);
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
    flop[0] = NULL;
    flop[1] = NULL;
    flop[2] = NULL;
    turn = NULL;
    river = NULL;
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
    //never happens
    return NULL;
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
    //never happens
    return -1;
}

void Game::flipFlop(bool verbose)
{
    discardNextCard();
    flop[0] = flipNextCard();
    flop[1] = flipNextCard();
    flop[2] = flipNextCard();
    if (verbose)
        printCardArray(flop, 3);
}

void Game::flipTurn(bool verbose)
{
    discardNextCard();
    turn = flipNextCard();
    if (verbose)
        turn->printCard();
}

void Game::flipRiver(bool verbose)
{
    discardNextCard();
    river = flipNextCard();
    if (verbose)
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

void Game::swap(Card **a, Card **b)
{
    Card *temp = *a;
    *a = *b;
    *b = temp;
}

void Game::shuffleDeck(int start)
{
    // Use a different seed value so that we don't get same
    // result each time we run this program
    srand (time(NULL));
 
    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = TOTAL_CARDS-1; i >= start; i--)
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
//Heads up only
int Game::determineWinner()
{
    //Check if everyone folded but one person
    for (int i = 0; i < numPlayers; ++i)
    {
        if (checkLastPlayerRemaining(players[i]) == true)
        {
            givePotToWinner(players[i]);
            return i;
        }
    }
    
    int equalHands = 0;
    Hand hands[numPlayers];
    Hand best = NOTHING;
    int playerIndex = 0;
    for (int i = 0; i < numPlayers; ++i) 
    {
        hands[i] = players[i]->bestHand(flop, turn, river, true);
        if (hands[i] > best)
        {
            best = hands[i];
            playerIndex = i;
            equalHands = 0;
        }
        else if (hands[i] == best)
        {
            equalHands = 1;
        }        
    }

    if (equalHands == 1)
    {
        splitPot();
        return SPLIT;
    }
    else
    {
        givePotToWinner(players[playerIndex]);
    }

    return playerIndex;
}

void Game::splitPot()
{
    cout << "Split pot" << endl;
    for (int i = 0; i < numPlayers; ++i)
    {
        players[i]->addChips((int)(pot/numPlayers));
        cout << "Player " << i << ": $" << players[i]->getChipCount() << endl;
    }
    pot = 0;
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

    int raiseCount = 0;
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
            move = getMove();
            me->doMove(move, getPlayerIndex(me), getPreviousPlayer(turn), false);
        }
        else
        {
            NodeState *state = new NodeState(this, turn);
            move = UCTSearch(state, UCT_DEPTH);
            if (move == BET)
            {
                raiseCount++;
            }
            if (raiseCount > 5)
            {
                raiseCount = 0;
                move = CHECK;
            }
            move = turn->doMove(move, getPlayerIndex(turn), getPreviousPlayer(turn), false);
            delete state;
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

Card** Game::getFlop()
{
    return flop;
}

Card* Game::getTurn()
{
    return turn;
}

Card* Game::getRiver()
{
    return river;
}

Card* Game::getCard(Card *card)
{
    if (card == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < TOTAL_CARDS; ++i)
    {
        if (deck[i] == NULL)
            cout << "FUCK" << endl;
        if (card->getSuit() == deck[i]->getSuit() && card->getCardValue() == deck[i]->getCardValue())
        {
            return deck[i];
        }
    }
    //never happens
    return NULL;
}

void Game::setupAIGame(Player *player)
{
    shuffleDeck(0);
    Card *c1 = getCard(player->getHand()[0]);
    Card *c2 = getCard(player->getHand()[1]);
    if (player == players[0])
    {
        swap(&c1, &deck[0]);
        swap(&c2, &deck[2]);
    }
    else if (player == players[1])
    {
        swap(&c1, &deck[1]);
        swap(&c2, &deck[3]);
    }
    distributeCards();

    if (flop[0] == NULL || flop[1] == NULL || flop[2] == NULL)
    {
        flipFlop(false);
    }
    else
    {
        swap(&flop[0], &deck[5]);
        swap(&flop[1], &deck[6]);
        swap(&flop[2], &deck[7]);
        deckPointer+=4;
    }
    if (turn == NULL)
    {
        flipTurn(false);
    }
    else
    {
        swap(&turn, &deck[9]);
        deckPointer+=2;
    }
    if (river == NULL)
    {
        flipRiver(false);
    }
    else
    {
        swap(&river, &deck[11]);
        deckPointer+=2;
    }
}

void Game::aiSwap(Player *player, bool fl, bool tu, bool ri)
{
    shuffleDeck(3);
    player->getHand()[0] = deck[4];
    player->getHand()[1] = deck[5];
    if (fl)
    {
        flop[0] = deck[6];
        flop[1] = deck[7];
        flop[2] = deck[8];
        swap(&flop[0], &deck[5]);
        swap(&flop[1], &deck[6]);
        swap(&flop[2], &deck[7]);
    }
    if (tu)
    {
        turn = deck[9];
        swap(&turn, &deck[9]);
    }
    if (ri)
    {
        river = deck[10];
        swap(&river, &deck[11]);
    }
}
