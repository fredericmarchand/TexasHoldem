#ifndef NODE_H
#define NODE_H

class Node
{
public:
	Node();
	~Node();
	bool isVisited();
	float explorationExploitationRatio();
	int getVisits();

private:
	bool visited;
	float winRate;
	Node *parent;
	int visits;

};

#endif //NODE_H
