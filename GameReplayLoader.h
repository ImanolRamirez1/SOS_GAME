#ifndef GAMEREPLAYLOADER_H
#define GAMEREPLAYLOADER_H

#include <vector>
#include <string>
#include "MoveRecord.h"

class GameReplayLoader {
public:
    bool load(const std::string& filename);
    const std::vector<MoveRecord>& getMoves() const;

private:
    std::vector<MoveRecord> moves;
};

#endif
