#include "Player.h"
#include <cstdlib>
#include <iostream>
#include "CardUtil.h"

Player::Player()
{
    hand[0] = NULL;
    hand[1] = NULL;
    dealer = false;
    this->chips = 1000;
    state = CHECK;
    ai = true;
}

Player::Player(int chips, bool ai)
{
    hand[0] = NULL;
    hand[1] = NULL;
    dealer = false;
    this->chips = chips;
    state = CHECK;
    this->ai = ai;
}

Player::~Player()
{
    hand[0] = NULL;
    hand[1] = NULL;
}

void Player::addCardToHand(Card *card, int i)
{
    hand[i] = card;
}

int Player::getChipCount()
{
    return chips;
}

int Player::addChips(int pot)
{
    chips += pot;
}

bool Player::isDealer()
{
    return dealer;
}

bool Player::isAI()
{
    return ai;
}

void Player::setDealer(bool deal)
{
    dealer = deal;
}

void Player::printHand()
{
    if (hand[0] == NULL || hand[1] == NULL)
    {
        cout << "Something is null" << endl;
        return;
    }
    printCardArray(hand, 2);
}

Move Player::getState()
{
    return state;
}

void Player::setState(Move move)
{
    state = move;
}

bool Player::bet(int *pot, int value)
{
    bool allIn = false;

    if ((chips - value) <= 0) {
        allIn =  true;
        (*pot)+=chips;
        chips = 0;
    }
    else
    {
        (*pot)+=value;
        chips-=value;
    }

    return allIn;
}

void checkHand(Card **combo, Card **retCombo, Hand *maxValue)
{
    Hand value = NOTHING;
    value = evaluateHand(combo);
    if (value > *maxValue) 
    {
        *maxValue = value;
        for (int i = 0; i < 5; ++i)
        {
            retCombo[i] = combo[i];
        }
    }
}

Hand Player::bestHand(Card** flop, Card *turn, Card *river)
{
    Card *combo[5];
    Hand maxValue = NOTHING;
    Card *retCombo[5];

    combo[0] = hand[0]; combo[1] = hand[1]; combo[2] = flop[0]; combo[3] = flop[1]; combo[4] = flop[2];
    checkHand(combo, retCombo, &maxValue);
    combo[0] = hand[0]; combo[1] = hand[1]; combo[2] = flop[0]; combo[3] = flop[1]; combo[4] = turn;
    checkHand(combo, retCombo, &maxValue);
    combo[0] = hand[0]; combo[1] = hand[1]; combo[2] = flop[0]; combo[3] = flop[1]; combo[4] = river;
    checkHand(combo, retCombo, &maxValue);
    combo[0] = hand[0]; combo[1] = hand[1]; combo[2] = flop[0]; combo[3] = turn;    combo[4] = flop[2];
    checkHand(combo, retCombo, &maxValue);
    combo[0] = hand[0]; combo[1] = hand[1]; combo[2] = flop[0]; combo[3] = river;   combo[4] = flop[2];
    checkHand(combo, retCombo, &maxValue);
    combo[0] = hand[0]; combo[1] = hand[1]; combo[2] = turn;    combo[3] = flop[1]; combo[4] = flop[2];
    checkHand(combo, retCombo, &maxValue);
    combo[0] = hand[0]; combo[1] = hand[1]; combo[2] = river;   combo[3] = flop[1]; combo[4] = flop[2];
    checkHand(combo, retCombo, &maxValue);
    combo[0] = hand[0]; combo[1] = hand[1]; combo[2] = flop[0]; combo[3] = turn;    combo[4] = river;
    checkHand(combo, retCombo, &maxValue);
    combo[0] = hand[0]; combo[1] = hand[1]; combo[2] = turn;    combo[3] = flop[1]; combo[4] = river;
    checkHand(combo, retCombo, &maxValue);
    combo[0] = hand[0]; combo[1] = hand[1]; combo[2] = turn;    combo[3] = river;   combo[4] = flop[2];
    checkHand(combo, retCombo, &maxValue);

    combo[0] = hand[0]; combo[1] = turn;  combo[2] = flop[0]; combo[3] = flop[1]; combo[4] = flop[2];
    checkHand(combo, retCombo, &maxValue);
    combo[0] = hand[0]; combo[1] = river; combo[2] = flop[0]; combo[3] = flop[1]; combo[4] = flop[2];
    checkHand(combo, retCombo, &maxValue);
    combo[0] = hand[0]; combo[1] = turn;  combo[2] = flop[0]; combo[3] = flop[1]; combo[4] = river;
    checkHand(combo, retCombo, &maxValue);
    combo[0] = hand[0]; combo[1] = turn;  combo[2] = flop[0]; combo[3] = river;   combo[4] = flop[2];
    checkHand(combo, retCombo, &maxValue);
    combo[0] = hand[0]; combo[1] = turn;  combo[2] = river;   combo[3] = flop[1]; combo[4] = flop[2];
    checkHand(combo, retCombo, &maxValue);

    combo[0] = hand[1]; combo[1] = turn;  combo[2] = flop[0]; combo[3] = flop[1]; combo[4] = flop[2];
    checkHand(combo, retCombo, &maxValue);
    combo[0] = hand[1]; combo[1] = river; combo[2] = flop[0]; combo[3] = flop[1]; combo[4] = flop[2];
    checkHand(combo, retCombo, &maxValue);
    combo[0] = hand[1]; combo[1] = turn;  combo[2] = flop[0]; combo[3] = flop[1]; combo[4] = river;
    checkHand(combo, retCombo, &maxValue);
    combo[0] = hand[1]; combo[1] = turn;  combo[2] = flop[0]; combo[3] = river;   combo[4] = flop[2];
    checkHand(combo, retCombo, &maxValue);
    combo[0] = hand[1]; combo[1] = turn;  combo[2] = river;   combo[3] = flop[1]; combo[4] = flop[2];
    checkHand(combo, retCombo, &maxValue);

    if (retCombo == NULL)
    {
        cout << "retCombo is NULL" << endl;
    }

    printCardArray(retCombo, 5);

    return maxValue;
}
