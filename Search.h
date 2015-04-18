#ifndef SEARCH_H
#define SEARCH_H

#include "Node.h"
#include "Game.h"
#include "Player.h"
#include "NodeState.h"
#include <cstdlib>

#define DEBUG 0
#define UCT_DEPTH 3

static Move UCTSearch(NodeState *startState, int maxIter)
{
	Node *root = new Node(startState);
	for (int i = 0; i < maxIter; ++i)
	{
		Node *node = root;
		NodeState *state = root->getState();

		//Select
#if DEBUG == 1
		cout << "Select" << endl;
#endif
		while (node->getUntriedMoves()->empty() && !node->getChildren()->empty()) //node is fully expanded and non-terminal
		{
			node = node->getUCB();
			state->doMove(node->getMove());
		}

		//Expand
#if DEBUG == 1
		cout << "Expand" << endl;
#endif
		if (!node->getUntriedMoves()->empty()) //if we can expand (i.e., state/node is non-terminal)
		{
			srand ( time(NULL) );
        	Move move = node->getUntriedMoves()->at(rand() % (node->getUntriedMoves()->size()));
        	state->doMove(move);
        	node = node->addChild(move, state); //Add child and descend tree
		}
		
		//Rollout
#if DEBUG == 1
		cout << "Rollout" << endl;
#endif
		while (!state->getMoves()->empty()) //While state is non-terminal
		{
			srand ( time(NULL) );
			//cout << state->getMoves()->size() << endl;
			state->doMove(state->getMoves()->at(rand() % (state->getMoves()->size())));
		}

		//Backpropagate
#if DEBUG == 1
		cout << "Backpropagate" << endl;
#endif
		while (node != NULL)
		{
			node->update(state->getResult(node->playerJustMoved()));
			node = node->getParent();
		}
	}

	Move moveToDo;
	int highest = 0;
	for (int i = 0; i < root->getChildren()->size(); ++i)
	{
		Node *child = root->getChildren()->at(i);
		if (child->getVisits() > highest)
		{
			highest = child->getVisits();
			moveToDo = child->getMove();
		}
	}

	delete root;
	
	return moveToDo; //Return the move that was the most visited
}

#endif //SEARCH_H