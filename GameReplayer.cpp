#include "GameReplayer.h"
#include <SFML/System/Clock.hpp>


GameReplayer::GameReplayer(Board& b, GameMode& m)
    : board(b), mode(m) {
}

void GameReplayer::loadReplay(const std::vector<MoveRecord>& moves) {
    replayMoves = moves;
    index = 0;
}

bool GameReplayer::step()
{
    // Wait until enough time has passed
    if (replayClock.getElapsedTime().asMilliseconds() < replayDelayMs)
        return true; // keep replaying, but don’t advance

    // Reset timer for next move
    replayClock.restart();

    // No more moves?
    if (index >= (int)replayMoves.size())
        return false;

    auto& m = replayMoves[index++];
    board.set(m.row, m.col, m.letter);
    mode.onMove(board, m.row, m.col, m.isBlue);

    return true;
}

bool GameReplayer::finished() const {
    return index >= (int)replayMoves.size();
}
