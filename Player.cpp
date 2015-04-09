#include "Player.h"
#include <cstdlib>
#include <iostream>

Player::Player()
{
    hand[0] = NULL;
    hand[1] = NULL;
    isDealer = false;
    this->chips = 1000;
}

Player::Player(int chips)
{
    hand[0] = NULL;
    hand[1] = NULL;
    isDealer = false;
    this->chips = chips;
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

void Player::setDealer(bool deal)
{
    isDealer = deal;
}

void Player::printHand()
{
    if (hand[0] == NULL || hand[1] == NULL)
    {
        cout << "Something is null" << endl;
        return;
    }
    cout << "|----------|----------|" << endl;
    cout << "|          |          |" << endl;
    cout << "|          |          |" << endl;
    cout << "|   " << hand[0]->getValueSymbol() << hand[0]->getSuitSymbol() << "    |   " << hand[1]->getValueSymbol() << hand[1]->getSuitSymbol() << "    |" << endl;
    cout << "|          |          |" << endl;
    cout << "|          |          |" << endl;
    cout << "|----------|----------|" << endl;
}