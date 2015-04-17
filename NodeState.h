#ifndef STATE_H
#define STATE_H

#include "Game.h"
#include <vector>

class NodeState
{
public:
	NodeState(Game *game);
	NodeState(NodeState *state);
	~NodeState();
	Game* getData();
	vector<Move>* getMoves();
	void doMove(Move move);
	int getResult(bool pjm);

private:
	Game *game;
	//Known information
    /*Card *hand[2];
    Card *flop[3];
    Card *turn;
    Card *river;
    int chips;
    int opponentChips;
    int pot;*/
};

#endif //STATE_H