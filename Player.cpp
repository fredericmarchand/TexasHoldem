#include "Player.h"

Player::Player(int chips)
{
        hand[0] = NULL;
        hand[1] = NULL;
        isDealer = false;
        this.chips = chips;
}

Player::~Player()
{
        hand[0] = NULL;
        hand[1] = NULL;
}

void Player::newHand(Card *card)
{
        if (hand[0] == NULL)
            hand[0] = card;
        else
            hand[1] = card;
}

int Player::getChipCount()
{
        return chips;
}

int Player::setDealer(bool deal)
{
        isDealer = deal;
}
