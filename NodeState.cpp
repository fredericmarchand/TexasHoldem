#include "NodeState.h"
using namespace std;

NodeState::NodeState(Game *game)
{
	game = new Game(game);
}

NodeState::NodeState(NodeState *state)
{
	game = new Game(state->getData());
}

NodeState::~NodeState()
{
	delete game;
}

Game* NodeState::getData()
{
	return game;
}

vector<Move>* NodeState::getMoves()
{
	//find possible moves from state
	//add them to moves
	return NULL;
}

void NodeState::doMove(Move move)
{

}

int NodeState::getResult(bool playerJustMoved)
{
	return 0;
}