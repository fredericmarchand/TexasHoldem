#ifndef CARDUTIL_H
#define CARDUTIL_H

#include <cstdlib>
#include <iostream>
using namespace std;

typedef enum hands {
    NOTHING,
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH,
} Hand;

/* Cards must be sorted by value */
static Hand evaluateHand(Card *hand[])
{
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

static void sortCardArray(Card *cards[], int left, int right)
{
    int i = left, j = right;
    Card *tmp;
    Card *pivot = cards[(left + right) / 2];

    while (i <= j) 
    {
        while (cards[i]->getCardValue() < pivot->getCardValue())
        {
            i++;
        }
        while (cards[j]->getCardValue() > pivot->getCardValue())
        {
            j--;
        }
        if (i <= j) 
        {
            tmp = cards[i];
            cards[i] = cards[j];
            cards[j] = tmp;
            i++;
            j--;
        }
    }

    if (left < j)
    {
        sortCardArray(cards, left, j);
    }
    if (i < right)
    {
        sortCardArray(cards, i, right);
    }
}

static void printCardArray(Card *cards[], int count)
{
    for (int i = 0; i < count; ++i)
    {
        cout << "|----------|"; 
    }
    cout << endl;
    for (int i = 0; i < count; ++i)
    {
        cout << "|          |";
    }
    cout << endl;
    for (int i = 0; i < count; ++i)
    {
        cout << "|          |";
    }
    cout << endl;
    for (int i = 0; i < count; ++i)
    {
        cout << "|   " << cards[i]->getValueSymbol() << cards[i]->getSuitSymbol() << "    |";
    }
    cout << endl;
    for (int i = 0; i < count; ++i)
    {
        cout << "|          |";
    }
    cout << endl;
    for (int i = 0; i < count; ++i)
    {
        cout << "|          |";
    }
    cout << endl;
    for (int i = 0; i < count; ++i)
    {
        cout << "|----------|";
    }
    cout << endl;
}

#endif //CARDUTIL_H