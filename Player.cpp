#include "Player.h"
#include "Card.h"
#include <cstdlib>

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
