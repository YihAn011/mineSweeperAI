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
    agentX = _agentX;
    agentY = _agentY;
    uncovered.resize(rowDimension, std::vector<bool>(colDimension, false));
    std::srand(std::time(0));
    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================
};

Agent::Action MyAI::getAction( int number )
{
    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================

    if(number==0)
    {
        revealAdjacentZeros(agentX, agentY);
    
        return {UNCOVER, agentX, agentY+=1};
    }
    

    return {LEAVE,-1,-1};

    //return {LEAVE,-1,-1};
    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================

}


// ======================================================================
// YOUR CODE BEGINS
// ======================================================================
void MyAI::revealAdjacentZeros(int x, int y) {
    std::queue<std::tuple<int, int>> toReveal;
    toReveal.push(std::make_tuple(x, y));

    while (!toReveal.empty()) {
        auto [cx, cy] = toReveal.front();
        toReveal.pop();

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int nx = cx + dx;
                int ny = cy + dy;

                if (isInBounds(nx, ny) && !uncovered[ny][nx]) {
                    uncovered[ny][nx] = true;
                    int adjacentNumber = getNumber(nx, ny);
    
                    if (adjacentNumber == 0) {
                        toReveal.push(std::make_tuple(nx, ny));
                    }
                }
            }
        }
    }
}
bool MyAI::isInBounds( int c, int r )
{
    return ( 0 <= c && c < colDimension && 0 <= r && r < rowDimension );
}


// ======================================================================
// YOUR CODE ENDS
// ======================================================================
