#ifndef STATE_H
#define STATE_H

#include "Game.h"
#include <vector>

class NodeState
{
public:
	NodeState(Game *game, Player *player);
	NodeState(NodeState *state);
	~NodeState();
	Game* getData();
	Player* getPlayer();
	vector<Move>* getMoves();
	void doMove(Move move);
	int getResult(bool pjm);
	void randomize();

private:
	Game *game;
	Player *player;
	vector<Move> moves;
	bool flopNull;
	bool turnNull;
	bool riverNull;
};

#endif //STATE_H