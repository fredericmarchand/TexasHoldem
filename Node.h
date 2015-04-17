#ifndef NODE_H
#define NODE_H

#define ln log
#include "Card.h"
#include "NodeState.h"
#include <vector>
using namespace std;

class Node
{
public:
    Node();
    Node(NodeState *state);
    Node(Move move, Node *parent, NodeState *state);
    ~Node();
    Node* getUCB();
    int getVisits();
    int getWins();
    Move getMove();
    NodeState* getState();
    Node* getParent();
    vector<Move>* getUntriedMoves();
    vector<Node*>* getChildren();
    void update(int value);
    Node* addChild(Move move, NodeState *state);
    bool playerJustMoved();

private:
    int wins;
    Node *parent;
    int visits;
    Move move;
    vector<Node*> children;
    vector<Move> untriedMoves;
    NodeState *state;
};

#endif //NODE_H
