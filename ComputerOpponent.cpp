#include "ComputerOpponent.h"

ComputerOpponent::ComputerOpponent(GameRecorder& recorder)
    : rec(recorder)
{
}

void ComputerOpponent::makeMove(Board& board, GameMode& mode, bool isBlueTurn)
{
    char letter = getSelectedLetter();

    auto move = cpu.chooseMove(board, letter);
    int r = move.first;
    int c = move.second;

    if (!board.inBounds(r, c) || board.get(r, c) != ' ')
        return;

    board.set(r, c, letter);

    
    rec.recordMove(r, c, letter, isBlueTurn);

    mode.onMove(board, r, c, isBlueTurn);
}
