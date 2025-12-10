#ifndef COMPUTEROPPONENT_H
#define COMPUTEROPPONENT_H

#include "Player.h"
#include "ComputerPlayer.h"
#include "GameRecorder.h"

class ComputerOpponent : public Player {
public:
    
    ComputerOpponent(GameRecorder& recorder);

    bool isComputer() const override {
        return true;
    }

    void makeMove(Board& board, GameMode& mode, bool isBlueTurn) override;

    char getSelectedLetter() const override {
        return (rand() % 2 == 0 ? 'S' : 'O');
    }

private:
    ComputerPlayer cpu;
    GameRecorder& rec;    
};

#endif
