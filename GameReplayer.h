#ifndef GAMEREPLAYER_H
#define GAMEREPLAYER_H

#include <vector>
#include "Board.h"
#include "GameMode.h"
#include "MoveRecord.h"
#include <SFML/System/Clock.hpp>


class GameReplayer {
public:
    GameReplayer(Board& b, GameMode& m);

    void loadReplay(const std::vector<MoveRecord>& moves);
    bool step();        // play next recorded move
    bool finished() const;

private:
    Board& board;
    GameMode& mode;
    std::vector<MoveRecord> replayMoves;
    int index = 0;
    sf::Clock replayClock;
    const int replayDelayMs = 500;
};

#endif
