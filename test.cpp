#include "pch.h"




#include <gtest/gtest.h>
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