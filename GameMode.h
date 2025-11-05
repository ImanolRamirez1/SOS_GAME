#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <string>

class Board;

struct MoveResult {
    int points;           // points awarded this move 
    bool gameOver;        // whether the game just ended
    std::string message;  // final status text 
};

class GameMode {
public:
    virtual ~GameMode() = default;
    virtual MoveResult onMove(Board& b, int r, int c, bool isBlueTurn) = 0;
    virtual bool isOver(const Board& b) const = 0;
};

#endif
