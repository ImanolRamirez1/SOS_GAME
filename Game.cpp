










#include "Game.h"
#include "GameMode.h"      
#include "GameMode.h"      
#include "SimpleMode.h"
#include "GeneralMode.h"

#include <iostream>
#include <algorithm>
#include <optional>

using namespace std;


static constexpr int WINDOW_WIDTH = 800;
static constexpr int WINDOW_HEIGHT = 600;
static constexpr int BOARD_SIZE = 8;
static constexpr int CELL_SIZE = 40;
static constexpr int BOARD_OFFSET_X = 200;
static constexpr int BOARD_OFFSET_Y = 100;

Game::~Game() = default;

Game::Game()
    : window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "SOS Game")
    , font()
    , board(BOARD_SIZE, CELL_SIZE, BOARD_OFFSET_X, BOARD_OFFSET_Y, font)
    , mode(nullptr)
    , isSimpleMode(true), blueTurn(true)
    , blueChoosesS(true), redChoosesS(true)
    , gameOver(false), isTyping(false)
    , blueScore(0), redScore(0)
    , activeSize(BOARD_SIZE)
    , title(font, "SOS Game", 22u)
    , simpleLabel(font, "Simple game", 16u)
    , generalLabel(font, "General game", 16u)
    , blueLabel(font, "Blue player", 16u)
    , redLabel(font, "Red player", 16u)
    , turnLabel(font, "", 18u)
    , blueScoreLabel(font, "Score: 0", 16u)
    , redScoreLabel(font, "Score: 0", 16u)
    , statusLabel(font, "", 20u)
    , boardSizeLabel(font, "Board Size:", 18u)
    , inputText(font, std::to_string(BOARD_SIZE), 20u)
    , resetLabel(font, "Reset Board", 16u)
    , blueS(font, "S", 20u)
    , blueO(font, "O", 20u)
    , redS(font, "S", 20u)
    , redO(font, "O", 20u)
{
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(true);

    if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "Error loading font.\n";
        std::exit(1);
    }

    // Default strategy
    mode = std::make_unique<SimpleMode>();

    // Titles 
    title.setFillColor(sf::Color::Black);
    title.setPosition({ 250.f, 10.f });

    simpleLabel.setFillColor(sf::Color::Black);
    simpleLabel.setPosition({ 220.f, 40.f });

    generalLabel.setFillColor(sf::Color::Black);
    generalLabel.setPosition({ 370.f, 40.f });

    // Mode selector dots
    simpleSelect.setRadius(6.f);
    simpleSelect.setFillColor(sf::Color::Blue);
    simpleSelect.setPosition({ 200.f, 44.f });

    generalSelect.setRadius(6.f);
    generalSelect.setFillColor(sf::Color::Transparent);
    generalSelect.setOutlineColor(sf::Color::Blue);
    generalSelect.setOutlineThickness(1.f);
    generalSelect.setPosition({ 350.f, 44.f });

    // Player labels
    blueLabel.setFillColor(sf::Color::Black);
    blueLabel.setPosition({ 30.f, 90.f });

    redLabel.setFillColor(sf::Color::Black);
    redLabel.setPosition({ 520.f, 90.f });

    // S/O glyphs
    blueS.setFillColor(sf::Color::Black);
    blueS.setPosition({ 50.f, 120.f });
    blueO.setFillColor(sf::Color::Black);
    blueO.setPosition({ 50.f, 150.f });

    redS.setFillColor(sf::Color::Black);
    redS.setPosition({ 540.f, 120.f });
    redO.setFillColor(sf::Color::Black);
    redO.setPosition({ 540.f, 150.f });

    // S/O selection dots
    blueSelect.setRadius(5.f);
    blueSelect.setFillColor(sf::Color::Blue);
    blueSelect.setPosition({ 35.f, 125.f });

    redSelect.setRadius(5.f);
    redSelect.setFillColor(sf::Color::Red);
    redSelect.setPosition({ 525.f, 125.f });

    // Turn & score labels
    turnLabel.setPosition({ 200.f, 460.f });

    blueScoreLabel.setFillColor(sf::Color::Blue);
    blueScoreLabel.setPosition({ 30.f, 180.f });

    redScoreLabel.setFillColor(sf::Color::Red);
    redScoreLabel.setPosition({ 520.f, 180.f });

    statusLabel.setFillColor(sf::Color::Black);
    statusLabel.setPosition({ 200.f, 430.f });

    // Board size input
    boardSizeLabel.setFillColor(sf::Color::Black);
    boardSizeLabel.setPosition({ 540.f, 40.f });

    inputBox.setSize({ 60.f, 30.f });
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineThickness(2.f);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setPosition({ 640.f, 35.f });

    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition({ 650.f, 40.f });
    boardSizeStr = std::to_string(activeSize);
    inputText.setString(boardSizeStr);

    // Reset button
    resetBtn.setSize({ 120.f, 36.f });
    resetBtn.setPosition({ 320.f, 520.f });
    resetBtn.setFillColor(sf::Color(200, 200, 200));
    resetBtn.setOutlineColor(sf::Color::Black);
    resetBtn.setOutlineThickness(1.f);

    resetLabel.setFillColor(sf::Color::Black);
    resetLabel.setPosition({ resetBtn.getPosition().x + 10.f, resetBtn.getPosition().y + 8.f });
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        draw();
    }
}

bool Game::containsPoint(const sf::RectangleShape& r, float x, float y) {
    sf::FloatRect bounds{ r.getPosition(), r.getSize() };
    return bounds.contains({ x, y });
}

void Game::resetBoard() {
    board.reset();
    blueTurn = true;
    blueScore = redScore = 0;
    gameOver = false;
    winnerMsg.clear();
    blueScoreLabel.setString("Score: 0");
    redScoreLabel.setString("Score: 0");
    statusLabel.setString("");
}

void Game::updateBoardSize(int newSize) {
    board.setSize(newSize);
    activeSize = newSize;
    resetBoard();
    boardSizeStr = std::to_string(activeSize);
    inputText.setString(boardSizeStr);
}

void Game::handleEvents() {
    while (auto event = window.pollEvent()) {

        // Close window
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        // Mouse clicks
        else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            const int mx = mousePressed->position.x;
            const int my = mousePressed->position.y;

            // Focus input box
            if (containsPoint(inputBox, static_cast<float>(mx), static_cast<float>(my)))
                isTyping = true;
            else
                isTyping = false;
            inputBox.setOutlineColor(isTyping ? sf::Color::Blue : sf::Color::Black);

            // Mode toggle
            if (mx > 190 && mx < 230 && my > 40 && my < 60) {
                isSimpleMode = true;
                simpleSelect.setFillColor(sf::Color::Blue);
                generalSelect.setFillColor(sf::Color::Transparent);
                mode = std::make_unique<SimpleMode>();
            }
            if (mx > 340 && mx < 380 && my > 40 && my < 60) {
                isSimpleMode = false;
                generalSelect.setFillColor(sf::Color::Blue);
                simpleSelect.setFillColor(sf::Color::Transparent);
                mode = std::make_unique<GeneralMode>();
            }

            // Blue S/O toggle
            if (mx > 30 && mx < 90 && my > 120 && my < 140) {
                blueChoosesS = true;
                blueSelect.setPosition({ 35.f, 125.f });
            }
            if (mx > 30 && mx < 90 && my > 150 && my < 170) {
                blueChoosesS = false;
                blueSelect.setPosition({ 35.f, 155.f });
            }

            // Red S/O toggle
            if (mx > 520 && mx < 580 && my > 120 && my < 140) {
                redChoosesS = true;
                redSelect.setPosition({ 525.f, 125.f });
            }
            if (mx > 520 && mx < 580 && my > 150 && my < 170) {
                redChoosesS = false;
                redSelect.setPosition({ 525.f, 155.f });
            }

            // Reset
            if (containsPoint(resetBtn, static_cast<float>(mx), static_cast<float>(my))) {
                resetBoard();
            }

            // Board placement
            const int col = (mx - BOARD_OFFSET_X) / CELL_SIZE;
            const int row = (my - BOARD_OFFSET_Y) / CELL_SIZE;

            if (!gameOver && board.inBounds(row, col)) {
                if (board.get(row, col) == ' ') {
                    const char toPlace = blueTurn ? (blueChoosesS ? 'S' : 'O')
                        : (redChoosesS ? 'S' : 'O');
                    board.set(row, col, toPlace);

                    // Delegate to current mode
                    auto res = mode->onMove(board, row, col, blueTurn);

                    // Points (General mode)
                    if (res.points > 0) {
                        if (blueTurn) blueScore += res.points;
                        else          redScore += res.points;
                        blueScoreLabel.setString("Score: " + std::to_string(blueScore));
                        redScoreLabel.setString("Score: " + std::to_string(redScore));
                    }

                    // End?
                    if (res.gameOver) {
                        gameOver = true;
                        if (!res.message.empty()) {
                            // Simple mode decided the message
                            statusLabel.setString(res.message);
                        }
                        else {
                            // General mode: compare scores
                            if (blueScore > redScore) statusLabel.setString("Blue wins (General)!");
                            else if (redScore > blueScore) statusLabel.setString("Red wins (General)!");
                            else                            statusLabel.setString("It's a tie!");
                        }
                    }

                    // Next turn: in General, only switch if you didn't score
                    if (!gameOver) {
                        if (res.points == 0) blueTurn = !blueTurn;
                    }
                }
            }
        }
        // Typing for board size input
        else if (const auto* textEvt = event->getIf<sf::Event::TextEntered>()) {
            if (isTyping) {
                const uint32_t ch = textEvt->unicode;

                if (ch >= '0' && ch <= '9') {
                    if (boardSizeStr.size() < 2) boardSizeStr.push_back(static_cast<char>(ch));
                }
                else if (ch == 8) { // backspace
                    if (!boardSizeStr.empty()) boardSizeStr.pop_back();
                }
                else if (ch == 13 || ch == '\r' || ch == '\n') { // Enter
                    int s = 0;
                    if (!boardSizeStr.empty()) {
                        try { s = std::stoi(boardSizeStr); }
                        catch (...) { s = 0; }
                    }
                    if (s < 1) s = 1;
                    if (s > 8) s = 8;
                    updateBoardSize(s);
                    isTyping = false;
                }

                
                inputText.setString(boardSizeStr);
                inputBox.setOutlineColor(isTyping ? sf::Color::Blue : sf::Color::Black);
            }
        }
    }
}


void Game::draw() {
    window.clear(sf::Color(240, 240, 240));

    // Mode UI
    window.draw(title);
    window.draw(simpleLabel);
    window.draw(generalLabel);
    window.draw(simpleSelect);
    window.draw(generalSelect);

    // Players UI
    window.draw(blueLabel);
    window.draw(redLabel);
    window.draw(blueS);
    window.draw(blueO);
    window.draw(redS);
    window.draw(redO);
    window.draw(blueSelect);
    window.draw(redSelect);

    // Turn label
    if (blueTurn) {
        turnLabel.setString("Current turn: Blue");
        turnLabel.setFillColor(sf::Color::Blue);
    }
    else {
        turnLabel.setString("Current turn: Red");
        turnLabel.setFillColor(sf::Color::Red);
    }
    window.draw(turnLabel);

    // Scores / status
    window.draw(blueScoreLabel);
    window.draw(redScoreLabel);
    if (gameOver) window.draw(statusLabel);

    // Board
    board.draw(window);

    // Controls
    window.draw(resetBtn);
    window.draw(resetLabel);
    window.draw(boardSizeLabel);
    window.draw(inputBox);
    window.draw(inputText);

    window.display();
}