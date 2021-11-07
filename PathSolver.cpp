#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver(){
    
}

PathSolver::~PathSolver(){
}

void PathSolver::forwardSearch(Env env){

    //Intialize the open and closed list of nodes to be used with the pathfinder program
    nodesOpenList = new NodeList();
    nodesExplored = new NodeList();

    //Integers that store the row and column of the goal node
    int goalRow = 0;
    int goalCol = 0;

    //This for loop determines the row and column of the goal, and then assigns each value to the integers initialized above.
    for(int row = 0; row < ENV_DIM; row++){
      for(int col = 0; col < ENV_DIM; col++){
         if (env[row][col] == goal){
            goalRow = row;
            goalCol = col;
         }
      }
   }

    //Set create a node with the goal node's co-ordinates
   Node* goalNode = new Node(goalRow, goalCol, 0);
   //intialise the currentNode
   Node* currentNode = nullptr;
   int distTravelled = 0;

    //Find the starting position in the maze, input a 20*20 maze, set the current working node and add it to the open node list.
    for(int row = 0; row < ENV_DIM; ++row){
        for(int col = 0; col < ENV_DIM; ++col){
            if(env[row][col] == start){

                //TargetRow and TargetCol are used to track the current Row/Col to check when searching Up/down/left/right
                targetRow = row;
                targetCol = col;
                currentNode = new Node(row, col, 0);
                nodesOpenList->addElement(currentNode);

                //this initially sets our lowest manhattan distance to starting node.
                int currentMinDistance = nodesOpenList->getNode(0)->getEstimatedDist2Goal(goalNode);

                /*
                Tracks the index position in the open node list while comparing open/closed lists to determine which nodes can be added to closed. Essentially, estimated
                distances from nodes in the open list are compared, this integer keeps track of the array index in the open list of the smallest estimated distance
                */
                int minIndex = 0;

                /*
                Boolean to check to see if the current node is present on the Closed Node List. If there are no possible explorable nodes, and all current nodes
                have been explored/can't be added to the closed list. This boolean is a failsafe, used in th event that the goal is blocked from any possible pathing from
                the start. If nothing can be added and no path is found, it's flagged as false and the program determines that there is no possible path or nodes to be added.
                */
                bool addToClosed = true;

                //Boolean value to check whether to keep pathing (goal has not been found)
                bool path = true;

                //Path = true, until currentNode's ROW and COL are the same as the goalNode's ROW and COL.
                //While this is true, update the currentNode, copy it to the closed node list, and increment distance travelled from the start
                while(path){
                    /*
                    If the current node can be added to the explored list;
                    1. set it to having been explored in the open list
                    2. Create a copy of the current node
                    3. Add it to the explored list
                    4. Increment the distance travelled from the start
                    */
                    if(addToClosed){
                        currentNode->setExplorable(false);
                        Node* newCurrent = new Node(*currentNode);
                        nodesExplored->addElement(newCurrent);
                        distTravelled++;
                    }

                    //Update the current working Row and Column of the current node to be used to look for surrounding empty spaces
                    targetRow = currentNode->getRow();
                    targetCol = currentNode->getCol();

                    /*
                    Search to see if UP is an empty symbol
                    Create a node if it's empty.
                    The first for loop checks to see if it's already in the open list, if it is, do not add it again.
                    If it is not present, add it to the open list.
                    This code is repeated for DOWN, LEFT, RIGHT respectively. These directions used a #define for convenience declared in Types.h
                    */
                    if(DIR_UP == SYMBOL_EMPTY || DIR_UP == SYMBOL_GOAL){
                        bool addUpNode = true;
                        Node* nodeUp = new Node(currentNode->getRow()-1, currentNode->getCol(), distTravelled);
                        nodeUp->setExplorable(true);

                        for(int i = 0; i < nodesOpenList->getLength(); ++i){
                            if(nodeUp->getCol() == nodesOpenList->getNode(i)->getCol() && nodeUp->getRow() == nodesOpenList->getNode(i)->getRow()){
                                addUpNode = false;
                            }
                        }
                        if(addUpNode == true){
                            nodesOpenList->addElement(nodeUp);
                        }
                    }

                    if(DIR_DOWN == SYMBOL_EMPTY || DIR_DOWN == SYMBOL_GOAL){
                        bool addDownNode = true;
                        Node* nodeDown = new Node(currentNode->getRow()+1, currentNode->getCol(), distTravelled);
                        nodeDown->setExplorable(true);
                        
                        for(int i = 0; i < nodesOpenList->getLength(); ++i){
                            if(nodeDown->getCol() == nodesOpenList->getNode(i)->getCol() && nodeDown->getRow() == nodesOpenList->getNode(i)->getRow()){
                                addDownNode = false;
                            }
                        }
                        if(addDownNode == true){
                            nodesOpenList->addElement(nodeDown);
                        }
                    }

                    if(DIR_LEFT == SYMBOL_EMPTY || DIR_LEFT == SYMBOL_GOAL){
                        bool addLeftNode = true;
                        Node* nodeLeft = new Node(currentNode->getRow(), currentNode->getCol()-1, distTravelled);
                        nodeLeft->setExplorable(true);
                        
                        for(int i = 0; i < nodesOpenList->getLength(); ++i){
                            if(nodeLeft->getCol() == nodesOpenList->getNode(i)->getCol() && nodeLeft->getRow() == nodesOpenList->getNode(i)->getRow()){
                                addLeftNode = false;
                            }
                        }
                        if(addLeftNode == true){
                            nodesOpenList->addElement(nodeLeft);
                        }
                    }

                    if(DIR_RIGHT == SYMBOL_EMPTY || DIR_RIGHT == SYMBOL_GOAL){
                        bool addRightNode = true;
                        Node* nodeRight = new Node(currentNode->getRow(), currentNode->getCol()+1, distTravelled);
                        nodeRight->setExplorable(true);

                        for(int i = 0; i < nodesOpenList->getLength(); ++i){
                            if(nodeRight->getCol() == nodesOpenList->getNode(i)->getCol() && nodeRight->getRow() == nodesOpenList->getNode(i)->getRow()){
                                addRightNode = false;
                            }
                        }
                        if(addRightNode == true){
                            nodesOpenList->addElement(nodeRight);
                        }
                    }
                    /*
                    Retrieve the length of open/closed node lists. set the minDistance to the greatest possible distance in order to have 
                    a clean slate to compare all possible minimum distances to the goal presented by values in the open node list array.
                    */
                    if(nodesOpenList->getLength() > nodesExplored->getLength()){
                        currentMinDistance = MAXIMUM_DISTANCE;
                        /*
                        For every value in the closed node list, compare every value of the open node list to it.
                        with values that are not present in the closed list array, compare which of them has the smallest manhattan distance to the goal.
                        save the index of the open list node with the smallest distance to the goal. once every value has been compared, the node with the smallest distance is now
                        set as the current node
                        */
                        for(int i = 0; i < nodesExplored->getLength(); ++i){
                            for(int j = 0; j < nodesOpenList->getLength(); ++j){
                                if(nodesOpenList->getNode(j)->getExplorable() == true && nodesOpenList->getNode(j)->getEstimatedDist2Goal(goalNode) <= currentMinDistance){
                                    currentMinDistance = nodesOpenList->getNode(j)->getEstimatedDist2Goal(goalNode);
                                        minIndex = j;
                                        currentNode = nodesOpenList->getNode(minIndex);
                                } 
                            }
                        }
                    //If no nodes can be added to the close list, as every node on the open lsit has been explored, and the goal is yet to be found (i.e the goal is inaccessible)
                    //from the start, stop pathing and declare that the goal is unreachable, breaking the for loop.
                    }else{
                        addToClosed = false;
                        path = false;
                        /*
                        //Print out explored nodes in the case the goal cannot be located
                        std::cout << "Exiting Program, no Nodes to add" << std::endl;
                        std::cout << "Could not find path from start to goal" << std::endl;
                        for (int i = 0; i < nodesExplored->getLength(); ++i){
                            std::cout << "My sad and failed path was: " << i << ". " << " Row: " << nodesExplored->getNode(i)->getRow() << ", Col: " << nodesExplored->getNode(i)->getCol() 
                            << ", Est. Distance: " << nodesExplored->getNode(i)->getEstimatedDist2Goal(goalNode) << ", after travelling: " << nodesExplored->getNode(i)->getDistanceTraveled() << std::endl;
                        }
                        */
                    }
                    //If the goal node's Row and Col match the currentNode's Row and Col, declare that the goal has been reached, pathing has stopped and break the for loop
                    if(currentNode->getCol() == goalNode->getCol() && currentNode->getRow() == goalNode->getRow()){
                        path = false;
                        nodesExplored->addElement(currentNode);
                        /*
                        //std::cout << "GOAL HAS BEEN LOCATED! WOOHOO!" << std::endl;
                        //Printing out the explored nodes path to the goal from start.
                        for (int i = 0; i < nodesExplored->getLength(); ++i){
                            std::cout << "My ~super~ optimum path was: " << i << ". " << " Row: " << nodesExplored->getNode(i)->getRow() << ", Col: " << nodesExplored->getNode(i)->getCol() 
                            << ", Est. Distance: " << nodesExplored->getNode(i)->getEstimatedDist2Goal(goalNode) << ", after travelling: " << nodesExplored->getNode(i)->getDistanceTraveled() << std::endl;
                        }
                        */
                    }  
                }
            }
        }
    }
}

NodeList* PathSolver::getNodesExplored(){
    return nodesExplored;
}

NodeList* PathSolver::getPath(Env env){
    //Current index sets our current node to be the last array value in the pathList (deep copy of nodesExplored)
    int currentIndex = 0;
    NodeList* pathList = new NodeList(*nodesExplored);
    currentIndex = pathList->getLength();
    //Now that the currentIndex is set to the last value of pathList, the current node is selected from that array using its index
    Node* currentNode = pathList->getNode(currentIndex-1);

    //Initialise direction enum (defined in Types.h), which is used to track the current travelling direction when mapping the shortest route to the goal
    Direction direction = UP;

    //This bool holds the same purpose as the path bool in ForwardSearch() -> to ensure that the program closes when done pathing
    bool path = true;

    //Integers to track the current working Row/Col of the currentNode, used to determine what node to search Up/Down/Left/Right from (as above)
    int targetRow;
    int targetCol; 

    //Define the current smallest travel distance from the goal node
    int minDistance = currentNode->getDistanceTraveled();
    
    
    for(int row = 0; row < ENV_DIM; ++row){
        for(int col = 0; col < ENV_DIM; ++col){
            while(path){
                targetRow = currentNode->getRow();
                targetCol = currentNode->getCol();

                //Setting correct char charcaters in relation to their directions for illustrating the quickest path 
                if(direction == UP && env[targetRow][targetCol] != SYMBOL_GOAL && env[targetRow][targetCol] != SYMBOL_START){
                    env[targetRow][targetCol] = 'V';
                }else if(direction == DOWN && env[targetRow][targetCol] != SYMBOL_GOAL && env[targetRow][targetCol] != SYMBOL_START){
                    env[targetRow][targetCol] = '^';
                }else if(direction == LEFT && env[targetRow][targetCol] != SYMBOL_GOAL && env[targetRow][targetCol] != SYMBOL_START){
                    env[targetRow][targetCol] = '>';
                }else if(direction == RIGHT && env[targetRow][targetCol] != SYMBOL_GOAL && env[targetRow][targetCol] != SYMBOL_START){
                    env[targetRow][targetCol] = '<';
                }

                /*
                These four if statements work similarly to the statements in the ForwardSearch function.
                If a direction is empty OR the start AND it is present in the copied pathList, check the node's travel distance.
                The travel distance is then compared to minDistance - the int which tracks the current smallest travel distance.
                This integer is passed between each direction each time this part of the code is looped through, at the end of the
                four if statements, the next node in the closed list which is free, is then set as the current node with the smallest
                distance to the start symbol
                */
                if(DIR_UP == SYMBOL_EMPTY || DIR_UP == SYMBOL_START){
                    Node* nodeUp = new Node(currentNode->getRow()-1, currentNode->getCol());
                    for(int i = 0; i < pathList->getLength(); ++i){
                        if(nodeUp->getRow() == pathList->getNode(i)->getRow() && nodeUp->getCol() == pathList->getNode(i)->getCol()){
                            if(pathList->getNode(i)->getDistanceTraveled() < minDistance){
                                minDistance = pathList->getNode(i)->getDistanceTraveled();
                                currentNode = pathList->getNode(i);
                                direction = UP;
                            }
                        }
                    }
                }

                if(DIR_DOWN == SYMBOL_EMPTY || DIR_DOWN == SYMBOL_START){
                    Node* nodeDown = new Node(currentNode->getRow()+1, currentNode->getCol());
                    for(int i = 0; i < pathList->getLength(); ++i){
                        if(nodeDown->getRow() == pathList->getNode(i)->getRow() && nodeDown->getCol() == pathList->getNode(i)->getCol()){
                            if(pathList->getNode(i)->getDistanceTraveled() < minDistance){
                                minDistance = pathList->getNode(i)->getDistanceTraveled();
                                currentNode = pathList->getNode(i);
                                direction = DOWN;
                            }
                        }
                    }
                }

                if(DIR_LEFT == SYMBOL_EMPTY || DIR_LEFT == SYMBOL_START){
                    Node* nodeLeft = new Node(currentNode->getRow(), currentNode->getCol()-1);
                    for(int i = 0; i < pathList->getLength(); ++i){
                        if(nodeLeft->getRow() == pathList->getNode(i)->getRow() && nodeLeft->getCol() == pathList->getNode(i)->getCol()){
                            if(pathList->getNode(i)->getDistanceTraveled() < minDistance){
                                minDistance = pathList->getNode(i)->getDistanceTraveled();
                                currentNode = pathList->getNode(i);
                                direction = LEFT;
                            }
                        }
                    }
                }

                if(DIR_RIGHT == SYMBOL_EMPTY || DIR_RIGHT == SYMBOL_START){
                    Node* nodeRight = new Node(currentNode->getRow(), currentNode->getCol()+1);
                    for(int i = 0; i < pathList->getLength(); ++i){
                        if(nodeRight->getRow() == pathList->getNode(i)->getRow() && nodeRight->getCol() == pathList->getNode(i)->getCol()){
                            if(pathList->getNode(i)->getDistanceTraveled() < minDistance){
                                minDistance = pathList->getNode(i)->getDistanceTraveled();
                                currentNode = pathList->getNode(i);
                                direction = RIGHT;
                            }
                        }
                    }
                }
                /*
                //Check to see if the goal has been reached yet, if so; stop pathing. Super easy to calculate as it will always be the first
                //value in the pathList array as that's where both the open and closed lists start in forwardSearch()
                */

                //std::cout << "Current node Row: " << currentNode->getRow() << ", Col: " << currentNode->getCol() << ", Distance: " << currentNode->getDistanceTraveled() << std::endl;
                
                if(currentNode->getCol() == pathList->getNode(0)->getCol() && currentNode->getRow() == pathList->getNode(0)->getRow()){
                    path = false;
                    //std::cout << "I have returned to the start" << std::endl;
                }
            }
        }
    }
    return pathList;
}

//-----------------------------