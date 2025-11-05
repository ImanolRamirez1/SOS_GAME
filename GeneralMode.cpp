#include "GeneralMode.h"
#include "Board.h"



using namespace std;

MoveResult GeneralMode::onMove(Board& b, int r, int c, bool ) {
    int made = b.countNewSOSAt(r, c);
    if (b.isFull()) {
        return { made, true, "" };
    }
    return { made, false, "" };
}

bool GeneralMode::isOver(const Board& b) const {
    return b.isFull();
}

