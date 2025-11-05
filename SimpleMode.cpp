#include "SimpleMode.h"
#include "Board.h"
using namespace std;



MoveResult SimpleMode::onMove(Board& b, int r, int c, bool isBlueTurn) {
    int made = b.countNewSOSAt(r, c);
    if (made > 0) {
        return { 0, true, isBlueTurn ? "Blue wins!" : "Red wins!" };
    }
    if (b.isFull()) {
        return { 0, true, "It's a draw!" };
    }
    return { 0, false, "" };
}

bool SimpleMode::isOver(const Board& b) const {
    return b.isFull();
}
