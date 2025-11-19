













#include "Game.h"
#include "GameMode.h"
#include "SimpleMode.h"
#include "GeneralMode.h"
#include "ComputerPlayer.h"
#include <Random>
#include <iostream>
#include <algorithm>
#include <optional>

Game::~Game() = default;

static constexpr int WINDOW_WIDTH = 800;
static constexpr int WINDOW_HEIGHT = 600;
static constexpr int BOARD_SIZE = 8;
static constexpr int CELL_SIZE = 40;
static constexpr int BOARD_OFFSET_X = 200;
static constexpr int BOARD_OFFSET_Y = 100;



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
    , blueHumanLabel(font, "Human", 14u)
    , blueCpuLabel(font, "CPU", 14u)
    , redHumanLabel(font, "Human", 14u)
    , redCpuLabel(font, "CPU", 14u)
{
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(true);

    if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "Error loading font.\n";
        std::exit(1);
    }

    mode = std::make_unique<SimpleMode>();

    // Title
    title.setFillColor(sf::Color::Black);
    title.setPosition({ 250.f, 10.f });

    // Mode labels
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

    // S/O letters
    blueS.setFillColor(sf::Color::Black);
    blueS.setPosition({ 50.f, 120.f });

    blueO.setFillColor(sf::Color::Black);
    blueO.setPosition({ 50.f, 150.f });

    redS.setFillColor(sf::Color::Black);
    redS.setPosition({ 540.f, 120.f });

    redO.setFillColor(sf::Color::Black);
    redO.setPosition({ 540.f, 150.f });

    // S/O selectors
    blueSelect.setRadius(5.f);
    blueSelect.setFillColor(sf::Color::Blue);
    blueSelect.setPosition({ 35.f, 125.f });

    redSelect.setRadius(5.f);
    redSelect.setFillColor(sf::Color::Red);
    redSelect.setPosition({ 525.f, 125.f });

    // Scores
    blueScoreLabel.setFillColor(sf::Color::Blue);
    blueScoreLabel.setPosition({ 30.f, 180.f });

    redScoreLabel.setFillColor(sf::Color::Red);
    redScoreLabel.setPosition({ 520.f, 180.f });

    // Status
    statusLabel.setFillColor(sf::Color::Black);
    statusLabel.setPosition({ 200.f, 430.f });

    // Current turn 
    turnLabel.setFillColor(sf::Color::Black);
    turnLabel.setPosition({ 200.f, 460.f });

    // Board size label + input
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

   
    resetBtn.setSize({ 120.f, 36.f });
    resetBtn.setPosition({ 320.f, 520.f });
    resetBtn.setFillColor(sf::Color(200, 200, 200));
    resetBtn.setOutlineColor(sf::Color::Black);
    resetBtn.setOutlineThickness(1.f);

    resetLabel.setFillColor(sf::Color::Black);
    resetLabel.setPosition({ resetBtn.getPosition().x + 10.f,
                             resetBtn.getPosition().y + 8.f });

    blueHumanBtn.setRadius(7.f);
    blueHumanBtn.setFillColor(sf::Color::Blue);
    blueHumanBtn.setPosition({ 30.f, 210.f });

    blueCpuBtn.setRadius(7.f);
    blueCpuBtn.setFillColor(sf::Color::Transparent);
    blueCpuBtn.setOutlineColor(sf::Color::Blue);
    blueCpuBtn.setOutlineThickness(2.f);
    blueCpuBtn.setPosition({ 70.f, 210.f });

    redHumanBtn.setRadius(7.f);
    redHumanBtn.setFillColor(sf::Color::Red);
    redHumanBtn.setPosition({ 520.f, 210.f });

    redCpuBtn.setRadius(7.f);
    redCpuBtn.setFillColor(sf::Color::Transparent);
    redCpuBtn.setOutlineColor(sf::Color::Red);
    redCpuBtn.setOutlineThickness(2.f);
    redCpuBtn.setPosition({ 560.f, 210.f });

  
    blueHumanLabel.setFillColor(sf::Color::Black);
    blueHumanLabel.setPosition({ 30.f, 230.f });

    blueCpuLabel.setFillColor(sf::Color::Black);
    blueCpuLabel.setPosition({ 85.f, 230.f });

    redHumanLabel.setFillColor(sf::Color::Black);
    redHumanLabel.setPosition({ 520.f, 230.f });

    redCpuLabel.setFillColor(sf::Color::Black);
    redCpuLabel.setPosition({ 570.f, 230.f });
}

char Game::randomLetter() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, 1);
    return dist(gen) == 0 ? 'S' : 'O';
}



void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        updateComputerMove();
        draw();
    }
}

bool Game::containsPoint(const sf::RectangleShape& r, float x, float y) {
    sf::FloatRect bounds(r.getPosition(), r.getSize());
    return bounds.contains(sf::Vector2f{ x, y });   
}

void Game::resetBoard() {
    board.reset();
    blueTurn = true;
    blueScore = 0;
    redScore = 0;
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


void Game::updateComputerMove() {
    if (gameOver) return;

    bool cpuTurn =
        (blueTurn && blueIsComputer) ||
        (!blueTurn && redIsComputer);

    if (!cpuTurn) return;

    if (!waitingForCpuMove) {
        waitingForCpuMove = true;
        cpuClock.restart();
        return;
    }

    if (cpuClock.getElapsedTime().asMilliseconds() < 250)
        return;

    waitingForCpuMove = false;

    char letter = randomLetter();


    auto move = cpu.chooseMove(board, letter);
    int row = move.first;
    int col = move.second;

    if (!board.inBounds(row, col) || board.get(row, col) != ' ')
        return;

    board.set(row, col, letter);
    auto res = mode->onMove(board, row, col, blueTurn);

    if (res.points > 0) {
        if (blueTurn) blueScore += res.points;
        else          redScore += res.points;
        blueScoreLabel.setString("Score: " + std::to_string(blueScore));
        redScoreLabel.setString("Score: " + std::to_string(redScore));
    }

    if (res.gameOver) {
        gameOver = true;
        if (!res.message.empty()) statusLabel.setString(res.message);
        else {
            if (blueScore > redScore)      statusLabel.setString("Blue wins (General)!");
            else if (redScore > blueScore) statusLabel.setString("Red wins (General)!");
            else                           statusLabel.setString("It's a tie!");
        }
        return;
    }

    if (res.points == 0) blueTurn = !blueTurn;
}

void Game::handlePlayerTypeClick(int mx, int my) {
    auto inside = [&](sf::CircleShape& c) {
        sf::FloatRect r(c.getPosition(), sf::Vector2f{ 14.f, 14.f });
        return r.contains(sf::Vector2f{ (float)mx, (float)my });
        };

    if (inside(blueHumanBtn)) {
        blueIsComputer = false;
        blueHumanBtn.setFillColor(sf::Color::Blue);
        blueCpuBtn.setFillColor(sf::Color::Transparent);
    }
    if (inside(blueCpuBtn)) {
        blueIsComputer = true;
        blueCpuBtn.setFillColor(sf::Color::Blue);
        blueHumanBtn.setFillColor(sf::Color::Transparent);
    }
    if (inside(redHumanBtn)) {
        redIsComputer = false;
        redHumanBtn.setFillColor(sf::Color::Red);
        redCpuBtn.setFillColor(sf::Color::Transparent);
    }
    if (inside(redCpuBtn)) {
        redIsComputer = true;
        redCpuBtn.setFillColor(sf::Color::Red);
        redHumanBtn.setFillColor(sf::Color::Transparent);
    }
}




void Game::handleEvents() {
    while (auto event = window.pollEvent()) {

        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
            int mx = mouse->position.x;
            int my = mouse->position.y;

            handlePlayerTypeClick(mx, my);

            if (containsPoint(inputBox, (float)mx, (float)my)) {
                isTyping = true;
            }
            else {
                isTyping = false;
            }
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

            // Blue S/O
            if (mx > 30 && mx < 90 && my > 120 && my < 140) {
                blueChoosesS = true;
                blueSelect.setPosition({ 35.f,125.f });
            }
            if (mx > 30 && mx < 90 && my > 150 && my < 170) {
                blueChoosesS = false;
                blueSelect.setPosition({ 35.f,155.f });
            }

            // Red S/O
            if (mx > 520 && mx < 580 && my > 120 && my < 140) {
                redChoosesS = true;
                redSelect.setPosition({ 525.f,125.f });
            }
            if (mx > 520 && mx < 580 && my > 150 && my < 170) {
                redChoosesS = false;
                redSelect.setPosition({ 525.f,155.f });
            }

            // Reset
            if (containsPoint(resetBtn, (float)mx, (float)my)) {
                resetBoard();
            }

            // Human-only board input
            if ((blueTurn && blueIsComputer) || (!blueTurn && redIsComputer))
                return;

            // Board placement
            int col = (mx - BOARD_OFFSET_X) / CELL_SIZE;
            int row = (my - BOARD_OFFSET_Y) / CELL_SIZE;

            if (!gameOver && board.inBounds(row, col) && board.get(row, col) == ' ') {
                char letter = blueTurn ? (blueChoosesS ? 'S' : 'O')
                    : (redChoosesS ? 'S' : 'O');
                board.set(row, col, letter);

                auto res = mode->onMove(board, row, col, blueTurn);

                if (res.points > 0) {
                    if (blueTurn) blueScore += res.points;
                    else          redScore += res.points;
                    blueScoreLabel.setString("Score: " + std::to_string(blueScore));
                    redScoreLabel.setString("Score: " + std::to_string(redScore));
                }

                if (res.gameOver) {
                    gameOver = true;
                    if (!res.message.empty()) statusLabel.setString(res.message);
                    else {
                        if (blueScore > redScore)      statusLabel.setString("Blue wins (General)!");
                        else if (redScore > blueScore) statusLabel.setString("Red wins (General)!");
                        else                           statusLabel.setString("It's a tie!");
                    }
                }
                else if (res.points == 0) {
                    blueTurn = !blueTurn;
                }
            }
        }
        else if (const auto* textEvt = event->getIf<sf::Event::TextEntered>()) {
            if (isTyping) {
                uint32_t ch = textEvt->unicode;
                if (ch >= '0' && ch <= '9') {
                    if (boardSizeStr.size() < 2) boardSizeStr.push_back((char)ch);
                }
                else if (ch == 8 && !boardSizeStr.empty()) {
                    boardSizeStr.pop_back();
                }
                else if (ch == 13 || ch == '\r' || ch == '\n') {
                    int s = 0;
                    try { s = std::stoi(boardSizeStr); }
                    catch (...) {}
                    s = std::max(1, std::min(8, s));
                    updateBoardSize(s);
                    isTyping = false;
                }
                inputText.setString(boardSizeStr);
            }
        }
    }
}

void Game::draw() {
    window.clear(sf::Color(240, 240, 240));

    window.draw(title);
    window.draw(simpleLabel);
    window.draw(generalLabel);
    window.draw(simpleSelect);
    window.draw(generalSelect);

    window.draw(blueLabel);
    window.draw(redLabel);
    window.draw(blueS);
    window.draw(blueO);
    window.draw(redS);
    window.draw(redO);
    window.draw(blueSelect);
    window.draw(redSelect);

    if (blueTurn) {
        turnLabel.setString("Current turn: Blue");
        turnLabel.setFillColor(sf::Color::Blue);
    }
    else {
        turnLabel.setString("Current turn: Red");
        turnLabel.setFillColor(sf::Color::Red);
    }
    window.draw(turnLabel);

    window.draw(blueScoreLabel);
    window.draw(redScoreLabel);

    if (gameOver) window.draw(statusLabel);

    board.draw(window);

    window.draw(resetBtn);
    window.draw(resetLabel);
    window.draw(boardSizeLabel);
    window.draw(inputBox);
    window.draw(inputText);

    // CPU/Human Buttons
    window.draw(blueHumanBtn);
    window.draw(blueCpuBtn);
    window.draw(redHumanBtn);
    window.draw(redCpuBtn);
    window.draw(blueHumanLabel);
    window.draw(blueCpuLabel);
    window.draw(redHumanLabel);
    window.draw(redCpuLabel);


    window.display();
}



