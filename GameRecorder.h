#ifndef GAMERECORDER_H
#define GAMERECORDER_H

#include <vector>
#include <string>
#include "MoveRecord.h"

class GameRecorder {
public:
    void recordMove(int row, int col, char letter, bool isBlue);
    bool saveToFile(const std::string& filename) const;
    void clear();

private:
    std::vector<MoveRecord> moves;
};

#endif
