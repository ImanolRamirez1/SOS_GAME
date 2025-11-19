
#include <gtest/gtest.h>
#include "pch.h"
#include "Game.h"
using namespace std;

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}


static void NewSimple(Game& g) { g.reset(3); g.setModeSimple(); }
static void NewGeneral(Game& g) { g.reset(3); g.setModeGeneral(); }
static int  M(Game& g, int r, int c, char ch) { return g.playMove(r, c, ch); }

// simple
TEST(SimpleMode, RowSOSEndsGame) {
    Game g; NewSimple(g);
    M(g, 0, 0, 'S');   // B
    M(g, 1, 1, 'S');   // R 
    M(g, 0, 1, 'O');   // B
    M(g, 2, 2, 'S');   // R 
    EXPECT_EQ(M(g, 0, 2, 'S'), 1);
    EXPECT_TRUE(g.isGameOver());
    EXPECT_GE(g.blueScore(), 1);
}

TEST(SimpleMode, ScoreFreezesAfterGameOver) {
    Game g; NewSimple(g);
    M(g, 0, 0, 'S');   // B
    M(g, 0, 1, 'O');   // R
    EXPECT_EQ(M(g, 0, 2, 'S'), 1); // B 
    int b = g.blueScore(), r = g.redScore();
    M(g, 1, 1, 'S');  
    EXPECT_EQ(g.blueScore(), b);
    EXPECT_EQ(g.redScore(), r);
    EXPECT_TRUE(g.isGameOver());
}

// generall 
TEST(GeneralMode, MultipleScoresAccumulate) {
    Game g; NewGeneral(g);
    
    M(g, 0, 0, 'S');   // B
    M(g, 1, 0, 'S');   // R 
    M(g, 0, 1, 'O');   // B
    M(g, 1, 1, 'O');   // R 
    EXPECT_EQ(M(g, 0, 2, 'S'), 1); 
    EXPECT_TRUE(g.isBlueTurn()); 
    EXPECT_EQ(M(g, 2, 2, 'S'), 1);  // B diagonal score
    EXPECT_EQ(g.blueScore(), 2);
    EXPECT_EQ(g.redScore(), 0);
    EXPECT_FALSE(g.isGameOver());
}

TEST(GeneralMode, BoardFullEndsGame) {
    Game g; NewGeneral(g);
    M(g, 0, 0, 'S');   // B
    M(g, 1, 0, 'S');   // R 
    M(g, 0, 1, 'O');   // B
    M(g, 2, 0, 'S');   // R 
    EXPECT_EQ(M(g, 0, 2, 'S'), 1); 

    
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            
            M(g, r, c, 'S');
        }
    }

    EXPECT_TRUE(g.isGameOver());
    EXPECT_GE(g.blueScore(), 1);
}

//test if the choice is a a vlaid empty cell on empty board

TEST(ComputerPlayerTests, ChoosesEmptyCellOnEmptyBoard) {
    Board b(3);
    ComputerPlayer cpu;

    pair<int, int> move = cpu.chooseMove(b, 'S');

    EXPECT_TRUE(b.inBounds(move.first, move.second));
    EXPECT_EQ(b.get(move.first, move.second), ' ');
}

//test if sos winning move is picked
TEST(ComputerPlayerTests, PicksWinningMoveWhenAvailable) {
    Board b(3);
    ComputerPlayer cpu;

    // S _ S on top row → CPU as 'O' should pick (0,1)
    b.set(0, 0, 'S');
    b.set(0, 2, 'S');

    pair<int, int> move = cpu.chooseMove(b, 'O');

    EXPECT_EQ(move.first, 0);
    EXPECT_EQ(move.second, 1);

    // If we actually play the move, SOS should be formed
    b.set(move.first, move.second, 'O');
    EXPECT_EQ(b.countNewSOSAt(move.first, move.second), 1);
}

//test that the computer never chooses filled cell.

TEST(ComputerPlayerTests, NeverChoosesFilledCell) {
    Board b(3);
    ComputerPlayer cpu;

    // Fill almost all cells
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            b.set(r, c, 'S');
        }
    }
    // Make exactly one empty spot
    b.set(2, 2, ' ');

    pair<int, int> move = cpu.chooseMove(b, 'O');

    EXPECT_EQ(move.first, 2);
    EXPECT_EQ(move.second, 2);
}

