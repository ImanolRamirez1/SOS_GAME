
#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

using namespace std;


class Board {
public:
    // Creates an N×N board 
    Board(int size, int cellSize, int offsetX, int offsetY, const sf::Font& font);

    void draw(sf::RenderWindow& window);
    void reset();
    void setSize(int newSize);

    // Logic helpers
    bool inBounds(int r, int c) const;
    bool isFull() const;
    int  countNewSOSAt(int r, int c) const;

    // Access
    char get(int r, int c) const { return grid[r][c]; }
    void set(int r, int c, char ch) { grid[r][c] = ch; }
    int  size() const { return n; }

private:
    int n;
    int cell;
    int offX, offY;

    vector<vector<char>> grid;

    const sf::Font& font;    
    sf::Text        cellText;
    sf::RectangleShape line;
};

#endif
