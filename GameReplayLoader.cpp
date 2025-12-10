#include "GameReplayLoader.h"
#include <fstream>

bool GameReplayLoader::load(const std::string& filename) {
    moves.clear();

    std::ifstream in(filename);
    if (!in.is_open()) return false;

    MoveRecord m;
    int isBlueInt;

    while (in >> m.row >> m.col >> m.letter >> isBlueInt) {
        m.isBlue = (isBlueInt == 1);
        moves.push_back(m);
    }

    return true;
}

const std::vector<MoveRecord>& GameReplayLoader::getMoves() const {
    return moves;
}
