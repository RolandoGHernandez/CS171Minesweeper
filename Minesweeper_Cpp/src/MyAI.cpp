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
    cout << "Row/Col Dims: " << _rowDimension << "/" << _colDimension << endl;
    cout << "Total Mines: " << _totalMines << endl;
    cout << "Agent X/Y: " << _agentX + 1 << "/" << _agentY + 1 << endl;

    // construct local board representation
    for (int i = 0; i < _rowDimension; i++)
    {
        vector<int> col;
        for (int j = 0; j < _colDimension; j++)
        {
            col.push_back(-1);
        }
        localBoard.push_back(col);
    }

    // uncover agent starting position
    localBoard[_agentY][_agentX] = 0;

    // initialize variables
    numCoveredTiles = _rowDimension * _colDimension - 1;
    numMines = _totalMines;

    unsigned numOfOnes = 0;

    prevUncover = {_agentX, _agentY};
    cout << "Previous Uncover: " << prevUncover.X << " " << prevUncover.Y << endl;
    origAgent = {_agentX, _agentY};

    rowDim = _rowDimension;
    colDim = _colDimension;
    // change board test
    displayBoard();
};



Agent::Action MyAI::getAction( int number )
{
    cout << "Number: " << number << ", Previous Uncover: " << prevUncover.X << ", " << prevUncover.Y << endl;
    cout << "Covered Tiles: " << numCoveredTiles << ", Mines: " << numMines << endl;
    int tileX, tileY;
    //update board based on parameter
    updateBoard(number, prevUncover);
    displayBoard();

    // CAN CATCH ALL ONES HERE
    if (number == 1) numOfOnes++;

    cout << "Debug First" << endl;
    /*
    if (number == 0 && (prevUncover.X == origAgent.X && prevUncover.Y == origAgent.Y))
    {
        cout << "FIRST" << endl;
        if ((origAgent.X - 1 >= 0 && origAgent.Y - 1 >= 0) && (localBoard[origAgent.X - 1][origAgent.Y - 1] == -1))
        {
            cout << "SECOND" << endl;
            tileX = origAgent.X - 1;
            tileY = origAgent.Y - 1;
        }
    }
    else if (number == 0 &&
    */
    if (numCoveredTiles == numMines)
    {
        cout << "NUMBER OF ONES FOUND: " << numOfOnes << endl;
        return {LEAVE, -1, -1};
    }
    if (number == 0 || number == 1)
    {
        // bot left
        if (origAgent.X - 1 >= 0 && origAgent.X - 1 < colDim && origAgent.Y - 1 >= 0 && origAgent.Y - 1 < rowDim && localBoard[origAgent.X - 1][origAgent.Y - 1] == -1)
        {
            prevUncover = {origAgent.X - 1, origAgent.Y - 1};
            randTile.push_back(prevUncover);
            numCoveredTiles--;
            return {UNCOVER, origAgent.X - 1, origAgent.Y - 1};
        }
        // mid left
        if (origAgent.X - 1 >= 0 && origAgent.X - 1 < colDim && origAgent.Y >= 0 && origAgent.Y < rowDim && localBoard[origAgent.X - 1][origAgent.Y] == -1)
        {
            prevUncover = {origAgent.X - 1, origAgent.Y};
            randTile.push_back(prevUncover);
            numCoveredTiles--;
            return {UNCOVER, origAgent.X - 1, origAgent.Y};
        }
        // top left
        if (origAgent.X - 1 >= 0 && origAgent.X - 1 < colDim && origAgent.Y + 1 >= 0 && origAgent.Y + 1 < rowDim && localBoard[origAgent.X - 1][origAgent.Y + 1] == -1)
        {
            prevUncover = {origAgent.X - 1, origAgent.Y + 1};
            randTile.push_back(prevUncover);
            numCoveredTiles--;
            return {UNCOVER, origAgent.X - 1, origAgent.Y + 1};
        }
        // top mid
        if (origAgent.X >= 0 && origAgent.X < colDim && origAgent.Y + 1 >= 0 && origAgent.Y + 1 < rowDim && localBoard[origAgent.X][origAgent.Y + 1] == -1)
        {
            prevUncover = {origAgent.X, origAgent.Y + 1};
            randTile.push_back(prevUncover);
            numCoveredTiles--;
            return {UNCOVER, origAgent.X, origAgent.Y + 1};
        }
        // top right
        if (origAgent.X + 1 >= 0 && origAgent.X + 1 < colDim && origAgent.Y + 1 >= 0 && origAgent.Y + 1 < rowDim && localBoard[origAgent.X + 1][origAgent.Y + 1] == -1)
        {
            prevUncover = {origAgent.X + 1, origAgent.Y + 1};
            randTile.push_back(prevUncover);
            numCoveredTiles--;
            return {UNCOVER, origAgent.X + 1, origAgent.Y + 1};
        }
        // mid right
        if (origAgent.X + 1 >= 0 && origAgent.X + 1 < colDim && origAgent.Y >= 0 && origAgent.Y < rowDim && localBoard[origAgent.X + 1][origAgent.Y] == -1)
        {
            prevUncover = {origAgent.X + 1, origAgent.Y};
            randTile.push_back(prevUncover);
            numCoveredTiles--;
            return {UNCOVER, origAgent.X + 1, origAgent.Y};
        }
        // bot right
        if (origAgent.X + 1 >= 0 && origAgent.X + 1 < colDim && origAgent.Y - 1 >= 0 && origAgent.Y - 1 < rowDim && localBoard[origAgent.X + 1][origAgent.Y - 1] == -1)
        {
            prevUncover = {origAgent.X + 1, origAgent.Y - 1};
            randTile.push_back(prevUncover);
            numCoveredTiles--;
            return {UNCOVER, origAgent.X + 1, origAgent.Y - 1};
        }
        // bot mid
        if (origAgent.X >= 0 && origAgent.X < colDim && origAgent.Y - 1 >= 0 && origAgent.Y - 1 < rowDim && localBoard[origAgent.X][origAgent.Y - 1] == -1)
        {
            prevUncover = {origAgent.X, origAgent.Y - 1};
            randTile.push_back(prevUncover);
            numCoveredTiles--;
            return {UNCOVER, origAgent.X, origAgent.Y - 1};
        }

        Tile temp;
        bool localBoardCheck = false;
        while (randTile.size() > 0 && !localBoardCheck)
        {
            temp = randTile.back();
            randTile.pop_back();
            if (localBoard[temp.X][temp.Y] == 0)
            {   
                localBoardCheck = true;   
            }
        }

        origAgent = temp;
        prevUncover = {temp.X, temp.Y};
        return {UNCOVER, temp.X, temp.Y};
    
    }
    else if (number == 1 && randTile.size() > 0)
    {
        cout << "HOLY SHIT" << endl;
        Tile temp = randTile.back();
        origAgent = temp;
        randTile.pop_back();
        prevUncover = {temp.X, temp.Y};
        numCoveredTiles--;
        return {UNCOVER, temp.X, temp.Y};
    }
    else if (number == 1 && randTile.size() == 0)
    {
        cout << "FUCKING STUFF" << endl;
    }
    prevUncover = {tileX, tileY};
    cout << "Debug last" << endl;
    return {LEAVE, -1, -1};
}



void MyAI::updateBoard(int num, Tile prevUncover)
{
    localBoard[prevUncover.X][prevUncover.Y] = num;
}



void MyAI::uncoverAdjacents(int col, int row)
{
    if (col - 1 >= 0 && row - 1 >= 0) localBoard[col-1][row-1] = 0;
}

void MyAI::displayBoard()
{
    for (int i = rowDim - 1; i >= 0; i--)
    {
        for (int j = 0; j < colDim; j++)
        {
            cout << localBoard[j][i] << " ";
        }
        cout << endl;
    }
}
