#include "GeneralMode.h"
#include "Board.h"



MoveResult GeneralMode::onMove(Board& b, int r, int c, bool isBlueTurn)
{
    MoveResult result;

    
    result.points = b.countNewSOSAt(r, c);
    result.gameOver = false;
    result.message = "";

    
    bool full = true;
    for (int row = 0; row < b.getSize(); ++row)
    {
        for (int col = 0; col < b.getSize(); ++col)
        {
            if (b.get(row, col) == ' ')
            {
                full = false;
                break;
            }
        }
        if (!full) break;
    }

    
    if (full)
    {
        result.gameOver = true;
        result.message = "";
    }

    lastResult = result;  
    return result;
}

bool GeneralMode::isOver(const Board& b) const
{
    for (int r = 0; r < b.getSize(); ++r)
        for (int c = 0; c < b.getSize(); ++c)
            if (b.get(r, c) == ' ')
                return false;
    return true;
}
