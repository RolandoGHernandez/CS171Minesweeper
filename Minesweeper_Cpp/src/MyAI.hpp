// ======================================================================
// FILE:        MyAI.hpp
//
// AUTHOR:      Jian Li
//
// DESCRIPTION: This file contains your agent class, which you will
//              implement. You are responsible for implementing the
//              'getAction' function and any helper methods you feel you
//              need.
//
// NOTES:       - If you are having trouble understanding how the shell
//                works, look at the other parts of the code, as well as
//                the documentation.
//
//              - You are only allowed to make changes to this portion of
//                the code. Any changes to other portions of the code will
//                be lost when the tournament runs your code.
// ======================================================================

#ifndef MINE_SWEEPER_CPP_SHELL_MYAI_HPP
#define MINE_SWEEPER_CPP_SHELL_MYAI_HPP

#include "Agent.hpp"
#include <iostream> // temporary use
#include <vector>
#include <map>
#include <set>
#include <algorithm>

#include <queue>
using namespace std;

class MyAI : public Agent
{
private:
    struct Tile{
        int x = -1;
        int y = -1;
<<<<<<< Updated upstream
        int label = -1;
        unsigned effectiveLabel = 10;
        unsigned coveredNeighbors = 8;
        bool inQueue = false;
        bool isCovered = true;
        bool isFlag = false;
        bool isBomb = false;
=======
        unsigned effectiveLabel = 10;
        unsigned coveredNeighbors = 8;
        bool inQueue = false;
        bool logicCheck = false;
        bool covered = true;
        bool canUncover = false;
        bool isFlag = false;

>>>>>>> Stashed changes
        // to sort tiles vector by their label
        bool operator < (const Tile& other)
        {
            if (effectiveLabel == other.effectiveLabel)
            {
                return coveredNeighbors < other.coveredNeighbors;
            }
            else
            {
                return effectiveLabel < other.effectiveLabel;
            }
        }
        
    };

    bool debug = true;

    int rowDim;
    int colDim;
    int agentX;
    int agentY;

    unsigned numCoveredTiles;
    unsigned numMines;

    vector<Tile*> tiles;
<<<<<<< Updated upstream
=======
    vector<Tile*> ones;
>>>>>>> Stashed changes
    vector<Tile*> bombs;
    vector<vector<Tile>> board;


public:
    MyAI ( int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY );
    Action getAction ( int number ) override;
<<<<<<< Updated upstream
    Action decision(int x, int y);
    static bool tileSort(Tile* t1, Tile* t2);
    void updateBoard(int x, int y, int number);
    void displayBoard();
    void displayBoardNeighbors();
    void displayTilesQ();
=======
    Action checkLLogic ( int x, int y );
    void checkCNELLogic ( int x, int y );
    Action decision( int x, int y );

    static bool tileSort( Tile* t1, Tile* t2 );

    void updateBoard( int x, int y, int number );
    void updateReturnedTile( int x, int y, int number);
    void updateNeighbors( int x, int y, int number);
    void updateEffectiveLabels( int x, int y, int number);

    void displayBoard();
    void displayBoardNeighbors();
    void displayTilesQ();
    void displayOnes();
>>>>>>> Stashed changes
   
};
#endif //MINE_SWEEPER_CPP_SHELL_MYAI_HPP
