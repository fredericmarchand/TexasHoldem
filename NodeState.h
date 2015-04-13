#ifndef STATE_H
#define STATE_H

#include "Player.h"
#include <vector>

class NodeState
{
public:
	NodeState();
	NodeState(NodeState *state);
	~NodeState();
	vector<Move>* getMoves();
	void doMove(Move move);
	int getResult(bool pjm);

private:
	//Known information
    Card *hand[2];
    Card *flop[3];
    Card *turn;
    Card *river;
    int chips;
    int opponentChips;
    int pot;
};

#endif //STATE_H