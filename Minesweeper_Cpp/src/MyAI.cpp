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
#include "Agent.hpp"

MyAI::MyAI ( int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY ) : Agent()
{
    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================
    rowDimension = _rowDimension;
    colDimension = _colDimension;
    totalMines = _totalMines;
    agentX = _agentX;
    agentY = _agentY;
    lastX = _agentX;
    lastY = _agentY;
    board = new Tile*[rowDimension];
    for (int i = 0; i < rowDimension; ++i)
    {
        board[i] = new Tile[colDimension];
    }
   
    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================
};

Agent::Action MyAI::getAction( int number )
{
    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================

     // 更新当前格子的状态，将其标记为已揭开，并记录数字
    board[lastX][lastY].uncovered = true;
    board[lastX][lastY].number = number;

    // 如果当前格子的数字是0，揭开相邻的格子
    if (number == 0)
    {
        uncoverAdjacentTiles(lastX, lastY);
    }
    else if(number ==1)
    {
        processNumberOne(lastX, lastY);
    }

    // 处理下一个动作
    if (!actions.empty())
    {
        Action nextAction = actions.front();
        actions.pop();
        // 更新lastX和lastY为下一个动作的坐标
        lastX = nextAction.x;
        lastY = nextAction.y;
        return nextAction;
    }

    // 如果没有其他动作要执行，离开游戏
    return {LEAVE, -1, -1};
    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================

}


// ======================================================================
// YOUR CODE BEGINS
// ======================================================================
MyAI::~MyAI()
{
    for (int i = 0; i < rowDimension; ++i)
    {
        delete[] board[i];
    }
    delete[] board;
}
bool MyAI::isInBounds( int c, int r )
{
    return ( 0 <= c && c < colDimension && 0 <= r && r < rowDimension );
}


void MyAI::uncoverAdjacentTiles(int x, int y)
{
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            int newX = x + dx;
            int newY = y + dy;
            if (dx != 0 || dy != 0)
            {
                if ((dx != 0 || dy != 0) && isInBounds(newX, newY) && !board[newX][newY].uncovered && !board[newX][newY].flag)
                {
                    actions.push({UNCOVER, newX, newY});
                }
            }
        }
    }
}


void MyAI::processNumberOne(int x, int y)
{
    int coveredCount = 0;
    std::vector<std::pair<int, int>> coveredTiles;

    // 遍历相邻的格子
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            int newX = x + dx;
            int newY = y + dy;
            if ((dx != 0 || dy != 0) && isInBounds(newX, newY))
            {
                if (!board[newX][newY].uncovered)
                {
                    coveredCount++;
                    coveredTiles.push_back({newX, newY});
                }
            }
        }
    }

    // 如果有且仅有一个未揭开的格子，标记它为地雷
    if (coveredCount == 1)
    {
        for (auto& tile : coveredTiles)
        {
            int newX = tile.first;
            int newY = tile.second;
            board[newX][newY].flag = true;
            actions.push({FLAG, newX, newY});
        }
    }
}
// ======================================================================
// YOUR CODE ENDS
// ======================================================================
