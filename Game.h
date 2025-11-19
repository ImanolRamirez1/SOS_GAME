#pragma once
#include <vector>
#include <utility>

using namespace std;

class Game {
    int n = 3;
    bool simpleMode = true;
    bool gameOver = false;
    bool blueTurn = true;
    int blue = 0, red = 0;
    vector<vector<char>> B;

public:
    Game() { reset(3); }

    void reset(int size) {
        n = size;
        B.assign(n, vector<char>(n, ' '));
        gameOver = false; blueTurn = true; blue = red = 0;
    }

    void setModeSimple() { simpleMode = true;  gameOver = false; }
    void setModeGeneral() { simpleMode = false; gameOver = false; }

    bool isGameOver() const { return gameOver; }
    bool isBlueTurn() const { return blueTurn; }
    int  blueScore()  const { return blue; }
    int  redScore()   const { return red; }

    int playMove(int r, int c, char ch) {
        if (gameOver || r < 0 || c < 0 || r >= n || c >= n || B[r][c] != ' ')
            return 0;

        B[r][c] = ch;
        int pts = countSOS(r, c);

        if (pts > 0) {
            if (blueTurn) blue += pts;
            else          red += pts;

            if (simpleMode)
                gameOver = true;     // Simple: first SOS ends the game
        }
        else {
            blueTurn = !blueTurn;    // no score → switch turn
        }

        if (!simpleMode && boardFull())
            gameOver = true;         // General: ends when board is full

        return pts;
    }

private:
    bool boardFull() const {
        for (auto& r : B)
            for (char c : r)
                if (c == ' ')
                    return false;
        return true;
    }

    bool in(int r, int c) const {
        return r >= 0 && c >= 0 && r < n && c < n;
    }

    int countSOS(int r, int c) const {
        static const int D[4][2] = { {1,0},{0,1},{1,1},{1,-1} };
        int tot = 0;

        for (auto& d : D) {
            int dr = d[0], dc = d[1];

            // O in the middle: S O S
            if (in(r - dr, c - dc) && in(r + dr, c + dc)) {
                if (B[r - dr][c - dc] == 'S' &&
                    B[r][c] == 'O' &&
                    B[r + dr][c + dc] == 'S')
                    tot++;
            }

            // S at the end: S O S contiguous 3
            if (in(r - 2 * dr, c - 2 * dc) && in(r - dr, c - dc)) {
                if (B[r - 2 * dr][c - 2 * dc] == 'S' &&
                    B[r - dr][c - dc] == 'O' &&
                    B[r][c] == 'S')
                    tot++;
            }
            if (in(r + 2 * dr, c + 2 * dc) && in(r + dr, c + dc)) {
                if (B[r][c] == 'S' &&
                    B[r + dr][c + dc] == 'O' &&
                    B[r + 2 * dr][c + 2 * dc] == 'S')
                    tot++;
            }
        }
        return tot;
    }
};

class Board {
private:
    int n;
    vector<vector<char>> grid;

public:
    Board(int size = 8)
        : n(size), grid(size, vector<char>(size, ' ')) {
    }

    int size() const { return n; }

    bool inBounds(int r, int c) const {
        return r >= 0 && r < n && c >= 0 && c < n;
    }

    bool isFull() const {
        for (const auto& row : grid)
            for (char ch : row)
                if (ch == ' ')
                    return false;
        return true;
    }

    char get(int r, int c) const {
        return grid[r][c];
    }

    void set(int r, int c, char ch) {
        grid[r][c] = ch;
    }

    // Same SOS logic as your main project
    int countNewSOSAt(int r, int c) const {
        if (!inBounds(r, c)) return 0;

        int cnt = 0;
        auto in = [&](int rr, int cc) {
            return rr >= 0 && rr < n && cc >= 0 && cc < n;
            };
        char v = grid[r][c];

        if (v == 'O') {
            if (in(r, c - 1) && in(r, c + 1) &&
                grid[r][c - 1] == 'S' && grid[r][c + 1] == 'S') cnt++;
            if (in(r - 1, c) && in(r + 1, c) &&
                grid[r - 1][c] == 'S' && grid[r + 1][c] == 'S') cnt++;
            if (in(r - 1, c - 1) && in(r + 1, c + 1) &&
                grid[r - 1][c - 1] == 'S' && grid[r + 1][c + 1] == 'S') cnt++;
            if (in(r - 1, c + 1) && in(r + 1, c - 1) &&
                grid[r - 1][c + 1] == 'S' && grid[r + 1][c - 1] == 'S') cnt++;
        }
        else if (v == 'S') {
            auto check = [&](int dr, int dc) {
                int r1 = r + dr, r2 = r + 2 * dr;
                int c1 = c + dc, c2 = c + 2 * dc;
                if (in(r1, c1) && in(r2, c2) &&
                    grid[r1][c1] == 'O' && grid[r2][c2] == 'S')
                    cnt++;
                };
            static const int dirs[8][2] = {
                {0,1},{0,-1},{1,0},{-1,0},
                {1,1},{-1,-1},{-1,1},{1,-1}
            };
            for (auto& d : dirs) check(d[0], d[1]);
        }
        return cnt;
    }
};

class ComputerPlayer {
public:
    // Board passed BY VALUE (copy) so we can safely test moves
    pair<int, int> chooseMove(Board b, char letter) {
        int n = b.size();

        // 1) Try to find a winning move (creates SOS)
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (b.get(r, c) == ' ') {
                    b.set(r, c, letter);
                    if (b.countNewSOSAt(r, c) > 0) {
                        return { r, c };
                    }
                    b.set(r, c, ' ');
                }
            }
        }

        // 2) Otherwise, pick first empty cell
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (b.get(r, c) == ' ') {
                    return { r, c };
                }
            }
        }

        // 3) Board full
        return { -1, -1 };
    }
};
