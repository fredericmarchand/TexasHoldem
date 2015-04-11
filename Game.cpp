#include "Game.h"
#include <cstdlib>
#include "Search.h"

Game::Game(int numPlayers)
{
    this->numPlayers = numPlayers;
    players = new Player*[numPlayers];
    for (int i = 0; i < numPlayers; ++i)
    {
        players[i] = new Player(1000);
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

Player** Game::getPlayers()
{
    return players;
}

int Game::getPlayerCount()
{
    return numPlayers;
}

void Game::flipFlop()
{
    discardNextCard();
    flop[0] = flipNextCard();
    flop[1] = flipNextCard();
    flop[2] = flipNextCard();
    flop[0]->printCard();
    flop[1]->printCard();
    flop[2]->printCard();
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
    for (int i = 52; i > 0; i--)
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
