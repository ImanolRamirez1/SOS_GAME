#ifndef SIMPLEMODE_H
#define SIMPLEMODE_H

#include "GameMode.h"

class SimpleMode : public GameMode {
public:
    MoveResult onMove(Board& b, int r, int c, bool isBlueTurn) override;
    bool isOver(const Board& b) const override;
};

#endif
