#ifndef COSC_ASSIGN_ONE_TYPES
#define COSC_ASSIGN_ONE_TYPES

#include <math.h> 


#define ENV_DIM                     20
#define NODE_LIST_ARRAY_MAX_SIZE    4*(ENV_DIM * ENV_DIM)

// A 2D array to represent the environment or observations
// REMEMBER: in a environment, the location (x,y) is found by maze[y][x]!
typedef char Env[ENV_DIM][ENV_DIM];

#define SYMBOL_WALL     '='
#define SYMBOL_EMPTY    '.'
#define SYMBOL_GOAL     'G'
#define SYMBOL_START    'S'

//direction from current node: Above/Below/Left/Right
#define DIR_UP env[targetRow-1][targetCol]
#define DIR_DOWN env[targetRow+1][targetCol]
#define DIR_LEFT env[targetRow][targetCol-1]
#define DIR_RIGHT env[targetRow][targetCol+1]

#define MAXIMUM_DISTANCE (ENV_DIM * ENV_DIM)

enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

#endif // COSC_ASSIGN_ONE_TYPES