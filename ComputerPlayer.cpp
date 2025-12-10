




#include "ComputerPlayer.h"
#include <cstdlib>
#include <vector>


std::pair<int, int> ComputerPlayer::chooseMove(Board& b, char letter)
{
    int n = b.getSize();

    
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (b.get(r, c) == ' ' && wouldMakeSOS(b, r, c, letter))
            {
                return { r, c }; // best move found
            }
        }
    }

    
    std::vector<std::pair<int, int>> legalMoves;

    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (b.get(r, c) == ' ')
            {
                legalMoves.push_back({ r, c });
            }
        }
    }

    // Safety: if board is full, return (0,0)
    if (legalMoves.empty())
        return { 0, 0 };

    int idx = rand() % legalMoves.size();
    return legalMoves[idx];
}



bool ComputerPlayer::wouldMakeSOS(Board& b, int r, int c, char letter)
{
    // Invalid position or space already filled
    if (!b.inBounds(r, c) || b.get(r, c) != ' ')
        return false;

    // Temporarily place the letter
    char old = b.get(r, c);
    b.set(r, c, letter);

    bool found = false;

    // Directions for SOS (8 directions)
    const int dirs[8][2] = {
        {0,1}, {1,0}, {1,1}, {1,-1},
        {0,-1}, {-1,0}, {-1,-1}, {-1,1}
    };

    // Check every direction pair around (r,c)
    for (auto& d : dirs)
    {
        int r1 = r - d[0];
        int c1 = c - d[1];
        int r2 = r + d[0];
        int c2 = c + d[1];

        if (b.inBounds(r1, c1) && b.inBounds(r2, c2))
        {
            // Pattern S O S
            if (b.get(r1, c1) == 'S' && b.get(r2, c2) == 'S' && letter == 'O')
            {
                found = true;
                break;
            }
        }
    }

    // Restore original board state
    b.set(r, c, old);
    return found;
}

