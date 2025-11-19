#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "Board.h"


class ComputerPlayer {
public:
    ComputerPlayer() = default;

    // Returns (row, col)
    std::pair<int, int> chooseMove(Board& b, char letter);

private:
    bool wouldMakeSOS(Board& b, int r, int c, char letter);
};

#endif
