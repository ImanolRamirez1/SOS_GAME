#include "GameRecorder.h"
#include <fstream>
#include <vector>


void GameRecorder::recordMove(int row, int col, char letter, bool isBlue) {
    moves.push_back({ row, col, letter, isBlue });
}

bool GameRecorder::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return false;

    for (const auto& m : moves) {
        out << m.row << " "
            << m.col << " "
            << m.letter << " "
            << (m.isBlue ? 1 : 0) << "\n";
    }
    return true;
}

void GameRecorder::clear() {
    moves.clear();
}
