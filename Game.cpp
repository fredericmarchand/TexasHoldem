#include "Game.h"
#include <cstdlib>
#include "Search.h"

Game::Game(int numPlayers)
{
    this->numPlayers = numPlayers;
    players = new Player*[numPlayers];
    dealer = new Dealer;
    for (int i = 0; i < numPlayers; ++i)
    {
        players[i] = new Player(1000);
    }
}

Game::~Game()
{
    for (int i = 0; i < numPlayers; ++i)
    {
        delete players[i];
    }
    delete [] players;
}

Player** Game::getPlayers()
{
    return players;
}

Dealer* Game::getDealer() {
    return dealer;
}

int Game::getPlayerCount()
{
    return numPlayers;
}

static int compareCards(const void *card1, const void *card2)
{
    return (*(Card *)card1).getCardValue() - (*(Card *)card2).getCardValue();
}

static int evaluateHand(Card *hand[])
{
    qsort(hand, 5, sizeof(Card), compareCards);
    int straight,flush,three,four,full,pairs;
    int k;

    straight = flush = three = four = full = pairs = 0;
    k = 0;

    //checks for flush
    while (k < 4 && hand[k]->getSuit() == hand[k+1]->getSuit())
    {
        k++;
    }

    if (k == 4)
    {
        flush = 1;
    }

    //checks for straight
    k = 0;
    while (k < 4 && hand[k]->getCardValue() == hand[k+1]->getCardValue()-1)
    {
        k++;
    }
    if (k == 4)
    {
        straight = 1;
    }

    //checks for fours
    for (int i = 0; i < 2; i++)
    {
        k = i;
        while (k < i+3 && hand[k]->getCardValue() == hand[k+1]->getCardValue())
        {
            k++;
        }
        if (k == i+3)
        {
            four = 1;
        }
    }

    //checks for threes and fullhouse
    if (!four)
    {
        for (int i = 0; i < 3; i++)
        {
            k = i;
            while (k < i+2 && hand[k]->getCardValue() == hand[k+1]->getCardValue())
            {
                k++;
            }
            if (k == i+2)
            {
                three = 1;
                if (i == 0)
                {
                    if (hand[3]->getCardValue() == hand[4]->getCardValue())
                    {
                        full = 1;
                    }
                }
                else if (i == 1){
                    if (hand[0]->getCardValue() == hand[4]->getCardValue())
                    {
                        full = 1;
                    }
                }
                else
                {
                    if (hand[0]->getCardValue() == hand[1]->getCardValue())
                    {
                        full = 1;
                    }
                }
            }
        }
    }

    if (straight && flush)
    {
        return STRAIGHT_FLUSH;
    }
    else if (four)
    {
        return FOUR_OF_A_KIND;
    }
    else if (full)
    {
        return FULL_HOUSE;
    }
    else if (flush)
    {
        return FLUSH;
    }
    else if (straight)
    {
        return STRAIGHT;
    }
    else if (three)
    {
        return THREE_OF_A_KIND;
    }

    //checks for pairs
    for (k = 0; k < 4; k++)
    {
        if (hand[k]->getCardValue() == hand[k+1]->getCardValue())
        {
            pairs++;
        }
    }

    if (pairs == 2)
    {
        return TWO_PAIR;
    }
    else if (pairs)
    {
        return PAIR;
    }
    else
    {
        return HIGH_CARD;
    }
}

