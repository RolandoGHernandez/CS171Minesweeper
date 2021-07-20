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
<<<<<<< Updated upstream
            
=======

>>>>>>> Stashed changes
        }
        board.push_back(col);
    }

    // initialize variables
<<<<<<< Updated upstream
    numCoveredTiles = _rowDimension * _colDimension - _totalMines;
=======
    numCoveredTiles = _rowDimension * _colDimension - _totalMines - 1;
>>>>>>> Stashed changes
    numMines = _totalMines;
    rowDim = _rowDimension;
    colDim = _colDimension;
    agentX = _agentX;
    agentY = _agentY;
};

<<<<<<< Updated upstream

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
=======
Agent::Action MyAI::getAction( int number )
{
    if (debug) 
    {
        cout << "Number: " << number << endl;
        cout << "AgentX/Y: " << agentX + 1 << "/" << agentY + 1 << endl;
        cout << "inQueue: " << board[agentY][agentX].inQueue << endl;
        cout << "logicCheck: " << board[agentY][agentX].logicCheck << endl;
        cout << "covered: " << board[agentY][agentX].covered << endl;
        cout << "canUncover: " << board[agentY][agentX].canUncover << endl;
        cout << "isFlag: " << board[agentY][agentX].isFlag << endl;
        cout << "Number of Covered Tiles Remaining: " << numCoveredTiles << endl;
        cout << endl;
    }

    // update our board of tiles with the information from the last action
    updateBoard(agentX, agentY, number);
    //displayBoard();

    // return action decided by decision function
    Action result = decision(agentX, agentY);

    //cout << result.x << "-" << result.y << endl;
    return result;
}

void MyAI::updateBoard(int x, int y, int number)
{
    // update board with returned number and agent coordinates
    updateReturnedTile(x, y, number);

    // if last action was UNCOVER
    if (number != -1 && !board[y][x].logicCheck)
    {
        updateNeighbors(x, y, number);
        updateEffectiveLabels(x, y, number);
        
    }
    // else if last action was FLAG
    else if (number == -1 && board[y][x].logicCheck)
    {
        if (debug)
            cout << "Updating Neighbors and EffectiveLabels" << endl;
        updateNeighbors(x, y, number);
        updateEffectiveLabels(x, y, number);
        
    }

    // display current updated information before moving onto decision
    if (debug)
    {
        displayBoardNeighbors();
        displayBoard();
    }
}

void MyAI::updateReturnedTile(int x, int y, int number)
{
    board[y][x].x = x;
    board[y][x].y = y;

    // condition to avoid resetting effective label of a tile that neighbors a FLAG
    if (number <= board[y][x].effectiveLabel)
    {
        board[y][x].effectiveLabel = number;
    }
    board[y][x].covered = false;
}

void MyAI::updateNeighbors(int x, int y, int number)
{
    // i increments/decrements y : j increments/decrements x
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

void MyAI::updateEffectiveLabels(int x, int y, int number)
{
    if (number == -1)
>>>>>>> Stashed changes
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
<<<<<<< Updated upstream
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
=======
                // if tile is within bounds of the board (and tile is not equal to the tile we just flagged)
                if ((i != 0 || j != 0) && x + j >= 0 && y + i >= 0 && x + j < colDim && y + i < rowDim)
                {
                    if(board[y + i][x + j].effectiveLabel)
                    {
                        board[y + i][x + j].effectiveLabel--; 
                        if (board[y + i][x + j].effectiveLabel == 1)
                        {
                            if (debug)
                            {
                                cout << "ONE ADDITION #1 " << board[y + i][x + j].x << "/" << board[y + i][x + j].y << endl;
                            }
                            ones.push_back(&board[y + i][x + j]);
                        }
                    }
>>>>>>> Stashed changes
                }
            }
        }
    }
<<<<<<< Updated upstream
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
=======
    else
    {
        if (debug)
        {
            cout << "UPDATING EFFECTIVE LABELS FOR SPECIFIC TILE AT: " << x + 1 << "/" << y + 1 << " and EL: " << board[y][x].effectiveLabel <<  endl;
        }
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                // if tile is within bounds of the board (and tile is not equal to the tile we just flagged)
                if ((i != 0 || j != 0) && x + j >= 0 && y + i >= 0 && x + j < colDim && y + i < rowDim && board[y + i][x + j].isFlag)
                {
                    if(board[y][x].effectiveLabel)
                    {
                        board[y][x].effectiveLabel--; 
                    }
                }
            }
        }
        if (board[y][x].effectiveLabel == 1)
        {
            if (debug)
            {
                cout << "ONES ADDITION #2 " << board[y][x].x << "/" << board[y][x].y << endl;
            }
            //ones.push_back(&board[y][x]);
        }
        if (debug)
        {
            cout << "ENDED UPDATING SPECIFIC TILE WITH EL: " << board[y][x].effectiveLabel << endl;
        }
    }
}

Agent::Action MyAI::decision(int x, int y)
{
    if (debug)
    {
        //cout << "decision called" << endl;
    }

    /*if (numCoveredTiles == 0)
    {
        if (debug)
        {
            cout << "WE WON!" << endl;
            cout << "Remaining Covered Tiles: " << numCoveredTiles << endl;
            cout << "Number of Mines: " << numMines << endl;
        }
        return {LEAVE, -1, -1};
    }
    */

    // adding tiles to be processed
    if (board[y][x].effectiveLabel == 0)
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if ((i != 0 || j != 0) && x + j >= 0 && y + i >= 0 && x + j < colDim && y + i < rowDim && !board[y + i][x + j].inQueue && board[y + i][x + j].covered)
                {
                    board[y + i][x + j].inQueue = true;
                    board[y + i][x + j].canUncover = true;
                    tiles.push_back(&board[y + i][x + j]);
                }
            }
        }
    }
    else if (board[y][x].effectiveLabel == 1)
    {
        if (debug) 
        {
            cout << "ONES ADDITION #3" << endl;
        }
        ones.push_back(&board[y][x]);
    }


    // sorts entire tile vector by effective label so 0's should process before 1's, on tie it uses coveredNeighbors
    // should contain all 0's then all 1's with fewest covered neighbors
    sort(tiles.begin(), tiles.end(), tileSort);
    if (debug)
    {
        displayTilesQ();
    }


    // processing tiles
    while (!tiles.empty())
    {
        agentX = tiles.front()->x;
        agentY = tiles.front()->y;
        tiles.erase(tiles.begin());
        board[agentY][agentX].inQueue = false;
        
        cout << "Processing Tile " << agentX + 1 << "/" << agentY + 1 << endl;

        if (board[agentY][agentX].canUncover && board[agentY][agentX].covered)
        {
            if (debug)
                cout << "\nDECISION IS UNCOVERING: " << agentX + 1 << "/" << agentY + 1 << endl;
            numCoveredTiles--;
            return {UNCOVER, agentX, agentY};
        }
    }


    // using L logic once all 0s are uncovered
    if (debug)
    {
        displayOnes();
    }
    

    Action temp;
    while (!ones.empty())
    {
        agentX = ones.front()->x;
        agentY = ones.front()->y;
        board[agentY][agentX].logicCheck = true;
        ones.erase(ones.begin());
        temp = checkLLogic(agentX, agentY);
        if (debug)
        {
            cout << "\nCHECKING L LOGIC AT: " << agentX + 1 << "/" << agentY + 1 << endl;
            cout << "L Logic Decides: ";
            if (temp.action == 1)
            {   
                cout << "NO L FOUND" << endl;
            }
            else
            {
                cout << "L FOUND, Flag" << endl;
            }
        }
        return temp;
    }

    cout << "WTIHASEFHIGAEIFGHJASDIRGHJAEIORGHJAEORHGJAERHOJAEROHJAJEHR" << endl;

    // using CNEL logic once all L's are found and updated effectiveNeighbors
    checkCNELLogic(x, y);
    while (!bombs.empty())
    {
        agentX = bombs.front()->x;
        agentY = bombs.front()->y;
        bombs.erase(bombs.begin());
        return {FLAG, agentX, agentY};
    }


    cout << "_.-*^ CAN YOU FEEL IT NOW MR. KRABS? ^*-._" << endl;
    return {LEAVE, -1, -1};
}

void MyAI::checkCNELLogic(int x, int y)
{
    if (debug)
    {
        cout << "\nCHECKING CNEL LOGIC AT: " << agentX + 1 << "/" << agentY + 1 << endl;
    }
    for (int i = 0; i < rowDim; i++)
    {
        for (int j = 0; j < colDim; j++)
        {
            if (board[i][j].effectiveLabel == board[i][j].coveredNeighbors)
            {
                // find the remaining neighbors
                for (int p = -1; p <= 1; p++)
                {
                    for (int q = -1; q <= 1; q++)
                    {
                        if ((p != 0 || q != 0) && x + q >= 0 && y + p >= 0 && x + q < colDim && y + p < rowDim && board[y + p][x + q].covered)
                        {
                            agentX = y + p;
                            agentY = x + q;
                            board[agentY][agentX].isFlag = true;
                            board[agentY][agentX].logicCheck = true;
                            if (debug)
                            {
                                cout << "Found CNEL Bomb to Flag @ " << agentX + 1 << "/" << agentY + 1 << endl;
                            }
                            // might need logic check here
                            bombs.push_back(&board[agentY][agentX]);
                        }
                    }
>>>>>>> Stashed changes
                }
            }
        }
    }
<<<<<<< Updated upstream

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
=======
}

Agent::Action MyAI::checkLLogic(int x, int y)
{
    bool left = false;
    bool top = false;
    bool right = false;
    bool bottom = false;

    // check left
    if (x - 1 >= 0 && board[y][x - 1].effectiveLabel == 1)
        left = true;

    // check top
    if (y + 1 < rowDim && board[y + 1][x].effectiveLabel == 1)
        top = true;

    // check right
    if (x + 1 < colDim && board[y][x + 1].effectiveLabel == 1)
        right = true;

    // check bottom
    if (y - 1 >= 0 && board[y - 1][x].effectiveLabel == 1)
        bottom = true;

    // if we have an L shape of tiles with effectiveLabel of 1, the suspect bomb tile is covered still, and is not already flagged
    if (left && bottom && board[y - 1][x - 1].covered && !board[y - 1][x - 1].isFlag)
    {
        agentX = x - 1;
        agentY = y - 1;
        board[agentY][agentX].isFlag = true;
        board[agentY][agentX].logicCheck = true;
        return {FLAG,  agentX, agentY};
    }
    else if (left && top && board[y + 1][x - 1].covered && !board[y + 1][x - 1].isFlag)
    {
        agentX = x - 1;
        agentY = y + 1;
        board[agentY][agentX].isFlag = true;
        board[agentY][agentX].logicCheck = true;
        return {FLAG,  agentX, agentY};
    }
    else if (right && top && board[y + 1][x + 1].covered && !board[y + 1][x + 1].isFlag)
    {
        agentX = x + 1;
        agentY = y + 1;
        board[agentY][agentX].isFlag = true;
        board[agentY][agentX].logicCheck = true;
        return {FLAG,  agentX, agentY};
    }
    else if (right && bottom && board[y - 1][x + 1].covered && !board[y - 1][x + 1].isFlag)
    {
        agentX = x + 1;
        agentY = y - 1;
        board[agentY][agentX].isFlag = true;
        board[agentY][agentX].logicCheck = true;
        return {FLAG, agentX, agentY};
    }
    else
    {
        return {UNCOVER, x, y};
    }
}
>>>>>>> Stashed changes

void MyAI::displayBoard()
{
    // print gameboard rows and entries
    // . == covered
    // # == flag

<<<<<<< Updated upstream
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

=======
    cout << "EFFECTIVE LABELS" << endl;

    for (int i = rowDim - 1; i >= 0; i--)
    {
        cout << i + 1 << ": ";

        if ( i < rowDim ) cout << " ";

        for (int j = 0; j < colDim; j++)
        {
            if (board[i][j].covered) cout << "." << "  ";
            else if (board[i][j].isFlag) cout << "#" << "  ";
            else cout << board[i][j].effectiveLabel << "  ";
        }
        cout << endl;
    }

    cout << "    ";

    // print separating lines
    for (int j = 0; j < colDim; j++)
    {
        if (j < 10) cout << "-  ";
        else cout << "-";
    }

    cout << "\n    ";

>>>>>>> Stashed changes
    // print numbers beneath board
    for (int j = 0; j < colDim; j++)
    {
        if (j < 10) cout << j + 1 << "  "; // two spaces for single digit
        else cout << j + 1 << " ";
    }
<<<<<<< Updated upstream

    cout << "\n" << endl;
}
=======

    cout << "\n" << endl;
}

>>>>>>> Stashed changes
void MyAI::displayBoardNeighbors()
{
    // print gameboard rows and entries
    // . == covered
    // # == flag
<<<<<<< Updated upstream
=======

    cout << "COVERED NEIGHBORS" << endl;

>>>>>>> Stashed changes
    for (int i = rowDim - 1; i >= 0; i--)
    {
        cout << i + 1 << ": ";

        if ( i < rowDim ) cout << " ";

        for (int j = 0; j < colDim; j++)
        {
<<<<<<< Updated upstream
            if (board[i][j].isCovered) cout << "." << "  ";
=======
            if (board[i][j].covered) cout << "." << "  ";
>>>>>>> Stashed changes
            else if (board[i][j].isFlag) cout << "#" << "  ";
            else cout << board[i][j].coveredNeighbors << "  ";
        }
        cout << endl;
    }

    cout << "    ";

<<<<<<< Updated upstream
=======
    // print separating lines
    for (int j = 0; j < colDim; j++)
    {
        if (j < 10) cout << "-  ";
        else cout << "-";
    }

    cout << "\n    ";

>>>>>>> Stashed changes
    // print numbers beneath board
    for (int j = 0; j < colDim; j++)
    {
        if (j < 10) cout << j + 1 << "  "; // two spaces for single digit
        else cout << j + 1 << " ";
    }

    cout << "\n" << endl;
}
<<<<<<< Updated upstream
void MyAI::displayTilesQ()
{
    cout << "\n" << "Tile Queue" << endl;
    for (int i = 0; i < tiles.size(); i++)
    {
        cout << "Tile " << tiles.at(i)->x + 1 << "/" << tiles.at(i)->y + 1 << " with EL: " << tiles.at(i)->effectiveLabel << " " << endl;
=======

void MyAI::displayTilesQ()
{
    cout << "\nTile Queue size: " << tiles.size() << endl;
    for (int i = 0; i < tiles.size(); i++)
    {
        cout << "Tile " << tiles.at(i)->x + 1 << "/" << tiles.at(i)->y + 1 << " with EL: " << tiles.at(i)->effectiveLabel << " and CN: " << tiles.at(i)->coveredNeighbors << endl;
    }
}

void MyAI::displayOnes()
{
    cout << "\nOnes Queue size: " << ones.size() << endl;
    for (int i = 0; i < ones.size(); i++)
    {
        cout << "One " << ones.at(i)->x + 1 << "/" << ones.at(i)->y + 1 << " with EL: " << ones.at(i)->effectiveLabel << " and CN: " << ones.at(i)->coveredNeighbors << endl;
>>>>>>> Stashed changes
    }
}

bool MyAI::tileSort(Tile* t1, Tile* t2)
{
    return *t1 < *t2;
}
