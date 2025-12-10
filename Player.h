#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include "GameMode.h"

class Player {
public:
    virtual ~Player() = default;

    // True if this player is controlled by the computer
    virtual bool isComputer() const = 0;

    // Perform a move
    virtual void makeMove(Board& board, GameMode& mode, bool isBlueTurn) = 0;

    // Returns 'S' or 'O' depending on player's selection
    virtual char getSelectedLetter() const = 0;
};

#endif
