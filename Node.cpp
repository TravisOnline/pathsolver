#include "Node.h"
#include <iostream>
#include <cstdlib>


Node::Node(int row, int col, int dist_traveled)
{
    this->row = int(row);
    this->col = int(col);
    this->dist_traveled = int(dist_traveled);
}

Node::Node(int row, int col){
    this->row = int(row);
    this->col = int(col);
}

Node::~Node(){
    delete this;
}

Node::Node(Node& other){
    this->row = other.row;
    this->col = other.col;
    this->dist_traveled = other.dist_traveled;
}

int Node::getRow(){
    return row;
}

int Node::getCol(){
    return col;
}

int Node::getDistanceTraveled(){
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

bool Node::getExplorable(){
    return explorable;
}

void Node::setExplorable(bool explorable){
    this->explorable = explorable;
}

int Node::getEstimatedDist2Goal(Node* goal){
    int goalRow = goal->getRow();
    int goalCol = goal->getCol();
    int currentRow = this->row;
    int currentCol = this->col;
    
    //added abs to each row/col section
    int manhattanDistance = (abs(currentRow - goalRow )+abs(currentCol - goalCol));
    //manhattanDistance = abs(manhattanDistance);

    return manhattanDistance;
}                          