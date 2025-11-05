
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Board.h"
#include <memory>      
using namespace std;






class GameMode;

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    // window & board
    sf::RenderWindow window;
    sf::Font         font;
    Board            board;

    // current strategy 
    unique_ptr<GameMode> mode;

    // labels/text 
    sf::Text title, simpleLabel, generalLabel;
    sf::Text blueLabel, redLabel, turnLabel;
    sf::Text blueScoreLabel, redScoreLabel, statusLabel;
    sf::Text boardSizeLabel, inputText, resetLabel;

    // glyphs
    sf::Text blueS, blueO, redS, redO;

    // widgets
    sf::RectangleShape inputBox, resetBtn;
    sf::CircleShape    simpleSelect, generalSelect, blueSelect, redSelect;

    // state
    bool isSimpleMode, blueTurn, blueChoosesS, redChoosesS, gameOver, isTyping;
    int  blueScore, redScore, activeSize;
    string winnerMsg, boardSizeStr;

    // helpers
    void handleEvents();
    void draw();
    void resetBoard();
    void updateBoardSize(int newSize);
    bool containsPoint(const sf::RectangleShape& r, float x, float y);
};

#endif

