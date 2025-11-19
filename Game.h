
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Board.h"
#include "ComputerPlayer.h"

#include <memory>      
using namespace std;






class GameMode;

class Game {
public:
    Game();
    ~Game();
    void run();

private:

    bool blueIsComputer = false;
    bool redIsComputer = false;

    ComputerPlayer cpu;  // NEW

    
    sf::CircleShape blueHumanBtn, blueCpuBtn;
    sf::CircleShape redHumanBtn, redCpuBtn;

    
    sf::Clock cpuClock;
    bool waitingForCpuMove = false;

   
   
    void handlePlayerTypeClick(int mx, int my);
    void updateComputerMove();

    // window & board
    sf::RenderWindow window;
    sf::Font         font;
    Board            board;

   
    unique_ptr<GameMode> mode;

    // labels/text 
    sf::Text title, simpleLabel, generalLabel;
    sf::Text blueLabel, redLabel, turnLabel;
    sf::Text blueScoreLabel, redScoreLabel, statusLabel;
    sf::Text boardSizeLabel, inputText, resetLabel;
    sf::Text blueS, blueO, redS, redO;
    sf::Text blueHumanLabel, blueCpuLabel;
    sf::Text redHumanLabel, redCpuLabel;
    

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
    char randomLetter();

};

#endif

