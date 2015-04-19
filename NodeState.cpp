#include "NodeState.h"
using namespace std;

NodeState::NodeState(Game *game, Player *player)
{
	this->game = new Game(game);
	this->player = this->game->getPlayers()[game->getPlayerIndex(player)];

	this->game->shuffleDeck(true);
	this->game->movePlayersCardsToFront();

	moves.push_back(FOLD);

	if (game->getNextPlayer(player)->getChipCount() >= 100 && player->getChipCount() >= 100)	//BET/RAISE
	{
		moves.push_back(BET);
	}

	if (game->getPreviousPlayer(player)->getState().bet > player->getState().bet)	
	{
		if (player->getChipCount() >= game->getPreviousPlayer(player)->getState().bet)
		{
			moves.push_back(CHECK);	//CALL
		}
	}
	else //CHECK
	{
		moves.push_back(CHECK);
	}
}

NodeState::NodeState(NodeState *state)
{
	game = new Game(state->getData());
	player = this->game->getPlayers()[game->getPlayerIndex(state->getPlayer())];

	game->shuffleDeck(true);
	game->movePlayersCardsToFront();

	moves.push_back(FOLD);

	if (game->getNextPlayer(player)->getChipCount() >= 100 && player->getChipCount() >= 100)	//BET/RAISE
	{
		moves.push_back(BET);
	}

	if (game->getPreviousPlayer(player)->getState().bet > player->getState().bet)	
	{
		if (player->getChipCount() >= game->getPreviousPlayer(player)->getState().bet)
		{
			moves.push_back(CHECK);	//CALL
		}
	}
	else //CHECK
	{
		moves.push_back(CHECK);
	}
}

NodeState::~NodeState()
{
	delete game;
}

Game* NodeState::getData()
{
	return game;
}

Player* NodeState::getPlayer()
{
	return player;
}

vector<Move>* NodeState::getMoves()
{
	return &moves;
}

void NodeState::doMove(Move move)
{
	player->doMove(move, game->getPlayerIndex(player), game->getPreviousPlayer(player), true);
	for (int i = 0; i < moves.size(); ++i)
	{
		if (moves.at(i) == move)
		{
			moves.erase(moves.begin()+i);
		}
	}
}

int NodeState::getResult(bool playerJustMoved)
{
	int p1 = game->getPlayers()[0]->bestHand(game->getFlop(), game->getTurn(), game->getRiver(), false);
	int p2 = game->getPlayers()[1]->bestHand(game->getFlop(), game->getTurn(), game->getRiver(), false);
	if (game->getPlayerIndex(player) == 0)
	{
		if (p1 > p2)
			return 1;
		else if (p1 == p2)
			return 0;
		else return -1;
	}
	else
	{
		if (p1 < p2)
			return 1;
		else if (p1 == p2)
			return 0;
		else return -1;
	}
	return 0;
}