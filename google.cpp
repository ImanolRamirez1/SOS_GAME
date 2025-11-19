
#include "Board.h"
using namespace std;

// AC 1.1 — Board(int size)
TEST(BoardTest, testBoardInitialization) {
    Board b(5);
    EXPECT_EQ(5, b.getSize()) << "Board size should match constructor input";
}

// AC 1.2 — getSize()
TEST(BoardTest, testBoardCellsMatch) {
    Board b(4);
    EXPECT_EQ(4, b.getSize());
}

// AC 4.1 / 6.1 — placeLetter() valid placement
TEST(BoardTest, testPlaceLetterUpdatesGUI) {
    Board b(3);
    EXPECT_TRUE(b.placeLetter(1, 1, 'S'));
    EXPECT_EQ('S', b.getCell(1, 1));
}

// “Other automated” — placement outside board
TEST(BoardTest, testPlaceLetterOutsideBoard) {
    Board b(3);
    EXPECT_FALSE(b.placeLetter(-1, 0, 'O'));
    EXPECT_FALSE(b.placeLetter(3, 3, 'S'));
}
