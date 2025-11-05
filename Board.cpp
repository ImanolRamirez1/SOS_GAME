

#include "Board.h"
#include <algorithm>




Board::Board(int size, int cellSize, int offsetX, int offsetY, const sf::Font& f)
    : n(size)
    , cell(cellSize)
    , offX(offsetX)
    , offY(offsetY)
    , grid(size, std::vector<char>(size, ' '))
    , font(f)
    , cellText(f, "", 22u)
{
    cellText.setFillColor(sf::Color::Black);
    line.setFillColor(sf::Color::Black);
}

void Board::draw(sf::RenderWindow& window) {
    // Grid
    for (int i = 0; i <= n; ++i) {
        // Vertical
        line.setSize({ 1.f, static_cast<float>(n * cell) });
        line.setPosition({ static_cast<float>(offX + i * cell), static_cast<float>(offY) });
        window.draw(line);

        // Horizontal
        line.setSize({ static_cast<float>(n * cell), 1.f });
        line.setPosition({ static_cast<float>(offX), static_cast<float>(offY + i * cell) });
        window.draw(line);
    }

    // Letters
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (grid[r][c] != ' ') {
                cellText.setString(std::string(1, grid[r][c]));
                cellText.setPosition({
                    static_cast<float>(offX + c * cell + 10),
                    static_cast<float>(offY + r * cell + 5)
                    });
                window.draw(cellText);
            }
        }
    }
}

void Board::reset() {
    for (auto& row : grid) std::fill(row.begin(), row.end(), ' ');
}

void Board::setSize(int newSize) {
    n = newSize;
    grid.assign(n, std::vector<char>(n, ' '));
}

bool Board::inBounds(int r, int c) const {
    return r >= 0 && r < n && c >= 0 && c < n;
}

bool Board::isFull() const {
    for (const auto& row : grid)
        for (char ch : row)
            if (ch == ' ') return false;
    return true;
}

int Board::countNewSOSAt(int r, int c) const {
    if (!inBounds(r, c)) return 0;

    int cnt = 0;
    auto in = [&](int rr, int cc) { return rr >= 0 && rr < n && cc >= 0 && cc < n; };
    char v = grid[r][c];

    if (v == 'O') {
        if (in(r, c - 1) && in(r, c + 1) && grid[r][c - 1] == 'S' && grid[r][c + 1] == 'S') cnt++;
        if (in(r - 1, c) && in(r + 1, c) && grid[r - 1][c] == 'S' && grid[r + 1][c] == 'S') cnt++;
        if (in(r - 1, c - 1) && in(r + 1, c + 1) && grid[r - 1][c - 1] == 'S' && grid[r + 1][c + 1] == 'S') cnt++;
        if (in(r - 1, c + 1) && in(r + 1, c - 1) && grid[r - 1][c + 1] == 'S' && grid[r + 1][c - 1] == 'S') cnt++;
    }
    else if (v == 'S') {
        auto check = [&](int dr, int dc) {
            int r1 = r + dr, r2 = r + 2 * dr, c1 = c + dc, c2 = c + 2 * dc;
            if (in(r1, c1) && in(r2, c2) && grid[r1][c1] == 'O' && grid[r2][c2] == 'S') cnt++;
            };
        static const int dirs[8][2] = {
            {0,1},{0,-1},{1,0},{-1,0},{1,1},{-1,-1},{-1,1},{1,-1}
        };
        for (auto& d : dirs) check(d[0], d[1]);
    }
    return cnt;
}