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
    state.move = CHECK;
    state.bet = 0;
    ai = true;
}

Player::Player(int chips, bool ai)
{
    hand[0] = NULL;
    hand[1] = NULL;
    dealer = false;
    this->chips = chips;
    state.move = CHECK;
    state.bet = 0;
    this->ai = ai;
}

Player::Player(Player *player)
{
    hand[0] = player->hand[0];
    hand[1] = player->hand[1];
    dealer = player->dealer;
    chips = player->chips;
    state.move = player->state.move;
    state.bet = player->state.bet;
    ai = player->ai;
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

int Player::removeChips(int amount)
{
    chips -= amount;
}

bool Player::isDealer()
{
    return dealer;
}

bool Player::isAI()
{
    return ai;
}

void Player::setAI(bool ai)
{
    this->ai = ai;
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
    cout << "chips: " << chips << endl;
}

State Player::getState()
{
    return state;
}

void Player::setState(Move move, int bet)
{
    state.move = move;
    state.bet = bet;
}

bool Player::bet(int value)
{
    bool allIn = false;

    if ((chips - value) <= 0) {
        allIn =  true;
        chips = 0;
        setState(BET, state.bet + chips);
    }
    else
    {
        chips -= value;
        setState(BET, state.bet + value);
    }

    return allIn;
}

void Player::check()
{
    setState(CHECK, state.bet);
}

void Player::fold()
{
    setState(FOLD, state.bet);
}

Move Player::doMove(Move move, int index, Player *last)
{
    //int prob = (rand() % 2)+1;
    cout << "Player " << index << ": ";
    switch (move) 
    {
        case 0:
            fold();
            cout << "fold" << endl;
            return FOLD;
        case 1:
            if (last->getState().bet >= state.bet)
            {
                bet(DEFAULT_BET + (last->getState().bet - getState().bet));
                cout << "raise " << DEFAULT_BET << " to " << getState().bet << endl;
            }
            else
            {
                bet(DEFAULT_BET);
                cout << "bet " << DEFAULT_BET << endl;
            }
            return BET;
        case 2:
        default:
            if (last->getState().bet > getState().bet)
            {
                bet(last->getState().bet - getState().bet);
                check();
                cout << "call" << endl;
            }
            else
            {
                check();
                cout << "check" << endl;
            }
            return CHECK;      
    }
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
