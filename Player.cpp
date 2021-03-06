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
    handsWon = 0;
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
    handsWon = 0;
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
    handsWon = player->handsWon;
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

Card** Player::getHand()
{
    return hand;
}

void Player::addChips(int pot)
{
    chips += pot;
}

void Player::removeChips(int amount)
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

Move Player::doMove(Move move, int index, Player *last, bool sim)
{
    //int prob = (rand() % 2)+1;
    if (!sim)
        cout << "Player " << index << ": ";
    switch (move) 
    {
        case FOLD:
            fold();
            if (!sim)
                cout << "fold" << endl;
            return FOLD;
        case BET:
            if (last->getState().bet >= state.bet)
            {
                bet(DEFAULT_BET + (last->getState().bet - getState().bet));
                if (!sim)
                    cout << "raise " << DEFAULT_BET << " to " << getState().bet << endl;
            }
            else
            {
                bet(DEFAULT_BET);
                if (!sim)
                    cout << "bet " << DEFAULT_BET << endl;
            }
            return BET;
        case CHECK:
        default:
            if (last->getState().bet > getState().bet)
            {
                bet(last->getState().bet - getState().bet);
                check();
                if (!sim)
                    cout << "call" << endl;
            }
            else
            {
                check();
                if (!sim)
                    cout << "check" << endl;
            }
            return CHECK;      
    }
}

void checkHand(Card **combo, Card **retCombo, Hand *maxValue)
{
    sortCardArray(combo, 0, 4);
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

Hand Player::bestHand(Card** flop, Card *turn, Card *river, bool verbose)
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

    if (verbose)
    {
        printCardArray(retCombo, 5);
    }

    return maxValue;
}

void Player::incHandsWon()
{
    handsWon += 1;
}

int Player::getHandsWon()
{
    return handsWon;
}