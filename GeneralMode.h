#ifndef GENERALMODE_H
#define GENERALMODE_H

#include "GameMode.h"

class GeneralMode : public GameMode {
public:
    MoveResult onMove(Board& b, int r, int c, bool isBlueTurn) override;
    bool isOver(const Board& b) const override;
};

#endif
