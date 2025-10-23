
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Board.h"

class Game {
public:
    Game();
    void run();

private:
    //reminder:::    sf;;Font font MUST COME BEFORE any sf;;text
    sf::RenderWindow window;
    sf::Font        font;
    Board           board;

    // Labels & text
    sf::Text title, simpleLabel, generalLabel;
    sf::Text blueLabel, redLabel, turnLabel;
    sf::Text blueScoreLabel, redScoreLabel, statusLabel;
    sf::Text boardSizeLabel, inputText, resetLabel;

    // S/O glyphs shown for each player
    sf::Text blueS, blueO, redS, redO;

    // Buttons / selectors
    sf::RectangleShape inputBox, resetBtn;
    sf::CircleShape    simpleSelect, generalSelect, blueSelect, redSelect;

    // State
    bool isSimpleMode, blueTurn, blueChoosesS, redChoosesS, gameOver, isTyping;
    int  blueScore, redScore, activeSize;
    std::string winnerMsg, boardSizeStr;

    // Helpers
    void handleEvents();
    void draw();
    void resetBoard();
    void updateBoardSize(int newSize);
    bool containsPoint(const sf::RectangleShape& r, float x, float y);
};

#endif
