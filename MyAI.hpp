// MyAI.hpp

#ifndef MINE_SWEEPER_CPP_SHELL_MYAI_HPP
#define MINE_SWEEPER_CPP_SHELL_MYAI_HPP

#include "Agent.hpp"
#include <iostream> // temporary use
#include <vector>
#include <map>
#include <set>
#include <algorithm>

#include <queue>
#include <random>
using namespace std;

class MyAI : public Agent
{
private:
    struct Tile{
        int X;
        int Y;
    };

    default_random_engine generator;

    vector<Tile> randTile;
    vector<Tile> onesTile;
    queue<Tile> uncoverQueue;
    vector<vector<int>> localBoard;
    unsigned numCoveredTiles;
    unsigned numMines;
    unsigned numOfOnes;
    Tile prevUncover;
    Tile origAgent;

    int rowDim;
    int colDim;

public:
    MyAI ( int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY );
    Action getAction ( int number ) override;
    Action checkMine ( Tile );
    void uncoverAdjacents(int col, int row );
    void updateBoard(int num, Tile prevUncover);
    void displayBoard ();
   
};
#endif //MINE_SWEEPER_CPP_SHELL_MYAI_HPP
