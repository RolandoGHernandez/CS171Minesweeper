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
    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================
    
    // First Step: Are we done? Check if #Covered Tiles = #Mines
    // otherwise we need to figure
    
    // Neighborhood 8 adjacent tiles to a tile
    // EffectiveLabel(x) = 0, all UnMarkedNeighbors(x)
    // EffectiveLabel(x) = Label(x) - NumMarkedNeighbors(x)
    // EffectiveLabel(x) = NumUnMarkedNeighbors(x), then all UnMarkedNeighbors(x) must be mines
    cout << "Row/Col Dims: " << _rowDimension << "/" << _colDimension << endl;
    cout << "Total Mines: " << _totalMines << endl;
    cout << "Agent X/Y: " << _agentX << "/" << _agentY << endl;

    // construct local board
    vector<vector<int>> localBoard(_rowDimension, vector<int> (_colDimension, -1));
    localBoard[_agentY][_agentX] = 0;

    // STEP 1: while ( totalUncovers != colDim*rowDim - totalMines )
    // STEP 2:     


    cout << getAction(1).action << endl;










   
    /*
    for (int i = _rowDimension - 1; i >=0; i--)
    {
        for (int j = 0; j < _colDimension; j++)
        {
            cout << localBoard[i][j] << " ";
        }
        cout << endl;
    }

    // first action should always be to uncover adjacent tiles
    uncoverAdjacents(localBoard, _agentY, _agentX);
    cout << "\n" << endl;

    for (int i = _rowDimension - 1; i >=0; i--)
    {
        for (int j = 0; j < _colDimension; j++)
        {
            cout << localBoard[i][j] << " ";
        }
        cout << endl;
    }
    */


    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================

};

Agent::Action MyAI::getAction( int number )
{
    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================


    return {UNCOVER, 0, 0};
    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================

}


// ======================================================================
// YOUR CODE BEGINS
// ======================================================================
vector<vector<int>> MyAI::uncoverAdjacents(vector<vector<int>> &localBoard, int col, int row)
{
    if (col - 1 >= 0 && row - 1 >= 0) localBoard[col-1][row-1] = 0;
    return localBoard;
}


// ======================================================================
// YOUR CODE ENDS
// ======================================================================
