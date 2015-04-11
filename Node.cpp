#include "Node.h"
#include <cmath>

Node::Node()
{
    visited = false; 
}

Node::~Node()
{
}

bool Node::isVisited()
{
    return visited;
}

float Node::explorationExploitationRatio()
{
    return sqrt(ln(parent->getVisits())/visits);
}

int Node::getVisits()
{
    return visits;
}
