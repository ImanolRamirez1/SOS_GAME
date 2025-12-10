

#include "SimpleMode.h"
#include "Board.h"
using namespace std;

MoveResult SimpleMode::onMove(Board& b, int r, int c, bool isBlueTurn) {
    int made = b.countNewSOSAt(r, c);

    MoveResult res;

    if (made > 0) {
        res = { 0, true, isBlueTurn ? "Blue wins!" : "Red wins!" };
    }
    else if (b.isFull()) {
        res = { 0, true, "It's a draw!" };
    }
    else {
        res = { 0, false, "" };
    }

    // ⭐ REQUIRED
    lastResult = res;

    return res;
}

bool SimpleMode::isOver(const Board& b) const {
    return b.isFull();
}
