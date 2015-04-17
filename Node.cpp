#include "Node.h"
#include <cmath>

Node::Node()
{
    parent = NULL;
    visits = 0;
    state = NULL;
}

Node::Node(NodeState *state)
{
    parent = NULL;
    visits = 0;
    this->state = state;
    untriedMoves = *(state->getMoves());
}

Node::Node(Move move, Node *parent, NodeState *state)
{
    parent = parent;
    visits = 0;
    this->move = move;
    this->state = state;
    untriedMoves = *(state->getMoves());
}

Node::~Node()
{
	for (int i = 0; i < children.size(); ++i)
	{
		delete children.at(i);
	}
}

//Node with highest upper confidence bound has highest urgency
Node* Node::getUCB()
{
	if (children.size() == 0)
	{
		return NULL;
	}

	Node *child = NULL;
	float UCB = 0.0;
	for (int i = 1; i < children.size(); ++i)
	{
		Node *c = children.at(i);
		float temp = (c->getWins()/c->getVisits() + sqrt(2*log(this->getVisits()/c->getVisits())));
		if (UCB > temp)
		{
			UCB = temp;
			child = c;
		}

	}
    return child;
}

int Node::getVisits()
{
    return visits;
}

int Node::getWins()
{
	return wins;
}

Move Node::getMove()
{
	return move;
}

NodeState* Node::getState()
{
	return state;
}

Node* Node::getParent()
{
	return parent;
}

//TODO: IMPLEMENT
bool Node::playerJustMoved()
{
	return false;
}

vector<Move>* Node::getUntriedMoves()
{
	return &untriedMoves;
}

vector<Node*>* Node::getChildren()
{
	return &children;
}

void Node::update(int result)
{
	visits += 1;
	wins += result;
}

Node* Node::addChild(Move move, NodeState *state)
{
	Node *child = new Node(move, this, state);
	for (int i = 0; i < untriedMoves.size(); i++)
	{
    	if (untriedMoves.at(i) == move)
    	{
    		untriedMoves.erase(untriedMoves.begin()+i);
    	}
	}
	children.push_back(child);

	return child;
}