// ======================================================================
// FILE:        MyAI.cpp
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

#include "MyAI.hpp"

MyAI::MyAI ( int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY ) : Agent()
{
    // Neighborhood 8 adjacent tiles to a tile
    // EffectiveLabel(x) = 0, all UnMarkedNeighbors(x)
    // EffectiveLabel(x) = Label(x) - NumMarkedNeighbors(x)
    // EffectiveLabel(x) = NumUnMarkedNeighbors(x), then all UnMarkedNeighbors(x) must be mines
    //cout << "Row/Col Dims: " << _rowDimension << "/" << _colDimension << endl;
    //cout << "Total Mines: " << _totalMines << endl;
    //cout << "Agent X/Y: " << _agentX + 1 << "/" << _agentY + 1 << endl;

    // construct local board representation
    for (int i = 0; i < _rowDimension; i++)
    {
        vector<Tile> col;
        for (int j = 0; j < _colDimension; j++)
        {
            Tile defaultTile;
            defaultTile.x = j;
            defaultTile.y = i;
            col.push_back(defaultTile);
            
        }
        board.push_back(col);
    }

    // initialize variables
    numCoveredTiles = _rowDimension * _colDimension - _totalMines;
    numMines = _totalMines;
    rowDim = _rowDimension;
    colDim = _colDimension;
    agentX = _agentX;
    agentY = _agentY;
};


void MyAI::updateBoard(int x, int y, int number)
{
    if (debug)
    {
        //cout << "updated Board" << endl;
    }


    // update board with returned number and agent coordinates
    board[y][x].x = x;
    board[y][x].y = y;
    board[y][x].label = number;
    board[y][x].effectiveLabel = number;
    board[y][x].isCovered = false;
 
    // update neighbors
    if (number != -1)
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                // tile is on boundary, must subtract out of bounds would-be neighbors
                if ((i != 0 || j != 0) && x + j < 0 || y + i < 0 || x + j >= colDim || y + i >= rowDim)
                {
                    if(board[y][x].coveredNeighbors)
                        board[y][x].coveredNeighbors--; 
                    //cout << "Tile @ " << x + 1 << "/" << y + 1 << " has " << board[y][x].coveredNeighbors << " neighbors left." << endl;
                }
                else if ((i != 0 || j != 0) && x + j >= 0 && y + i >= 0 && x + j < colDim && y + i < rowDim)
                {
                    if(board[y + i][x + j].coveredNeighbors)
                        board[y + i][x + j].coveredNeighbors--; 
                    //cout << "Tile @ " << x + j + 1 << "/" << y + i + 1 << " has " << board[y + i][x + j].coveredNeighbors << " neighbors left." << endl;
                }
            }
        }
    }
    displayBoardNeighbors();
}

Agent::Action MyAI::getAction( int number )
{
    if (debug) 
    {
        cout << "Number: " << number << endl;
        cout << "AgentX/Y: " << agentX + 1 << "/" << agentY + 1 << "\n" << endl;
    }

    // update our board of tiles with the information from the last action
    updateBoard(agentX, agentY, number);
    //displayBoard();

    // return action decided by decision function
    Action result = decision(agentX, agentY);

    //cout << result.x << "-" << result.y << endl;
    return result;
}

Agent::Action MyAI::decision(int x, int y)
{
    if (debug)
    {
        //cout << "decision called" << endl;
    }


    // add adjacent tiles to tiles queue
    if (board[y][x].effectiveLabel == 0)
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if ((i != 0 || j != 0) && x + j >= 0 && y + i >= 0 && x + j < colDim && y + i < rowDim && !board[y + i][x + j].inQueue)
                {
                    board[y + i][x + j].inQueue = true;
                    tiles.push_back(&board[y + i][x + j]);
                }
            }
        }
    }

    sort(tiles.begin(), tiles.end(), tileSort);
    //displayTilesQ();

    // process queue
    if (!tiles.empty())
    {
        agentX = tiles.front()->x;
        agentY = tiles.front()->y;
        tiles.erase(tiles.begin());
    }
    
    if (debug)
    {
        cout << "UNCOVERING: " << agentX + 1 << "/" << agentY + 1 << endl;
    }


    return {UNCOVER, agentX, agentY};
}

void MyAI::displayBoard()
{
    // print gameboard rows and entries
    // . == covered
    // # == flag
    for (int i = rowDim - 1; i >= 0; i--)
    {
        cout << i + 1 << ": ";

        if ( i < rowDim ) cout << " ";

        for (int j = 0; j < colDim; j++)
        {
            if (board[i][j].isCovered) cout << "." << "  ";
            else if (board[i][j].isFlag) cout << "#" << "  ";
            else cout << board[i][j].label << "  ";
        }
        cout << endl;
    }

    cout << "    ";

    // print numbers beneath board
    for (int j = 0; j < colDim; j++)
    {
        if (j < 10) cout << j + 1 << "  "; // two spaces for single digit
        else cout << j + 1 << " ";
    }

    cout << "\n" << endl;
}
void MyAI::displayBoardNeighbors()
{
    // print gameboard rows and entries
    // . == covered
    // # == flag
    for (int i = rowDim - 1; i >= 0; i--)
    {
        cout << i + 1 << ": ";

        if ( i < rowDim ) cout << " ";

        for (int j = 0; j < colDim; j++)
        {
            if (board[i][j].isCovered) cout << "." << "  ";
            else if (board[i][j].isFlag) cout << "#" << "  ";
            else cout << board[i][j].coveredNeighbors << "  ";
        }
        cout << endl;
    }

    cout << "    ";

    // print numbers beneath board
    for (int j = 0; j < colDim; j++)
    {
        if (j < 10) cout << j + 1 << "  "; // two spaces for single digit
        else cout << j + 1 << " ";
    }

    cout << "\n" << endl;
}
void MyAI::displayTilesQ()
{
    cout << "\n" << "Tile Queue" << endl;
    for (int i = 0; i < tiles.size(); i++)
    {
        cout << "Tile " << tiles.at(i)->x + 1 << "/" << tiles.at(i)->y + 1 << " with EL: " << tiles.at(i)->effectiveLabel << " " << endl;
    }
}

bool MyAI::tileSort(Tile* t1, Tile* t2)
{
    return *t1 < *t2;
}
