#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(char letterChoice = 'S')
        : letter(letterChoice) {
    }

    bool isComputer() const override {
        return false;
    }

  
    void makeMove(Board&, GameMode&, bool) override {}

    char getSelectedLetter() const override {
        return letter;
    }

    void setLetter(char c) {
        letter = c;
    }

private:
    char letter;
};

#endif
