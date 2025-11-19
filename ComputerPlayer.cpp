#include "ComputerPlayer.h"

// Test if placing S or O here makes an SOS.
bool ComputerPlayer::wouldMakeSOS(Board& b, int r, int c, char letter) {
    if (b.get(r, c) != ' ') return false;

    
    b.set(r, c, letter);
    int sos = b.countNewSOSAt(r, c);
    b.set(r, c, ' ');

    return (sos > 0);
}

std::pair<int, int> ComputerPlayer::chooseMove(Board& b, char letter) {
    int n = b.size();

    // Try to win
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (wouldMakeSOS(b, r, c, letter))
                return { r, c };
        }
    }

    // Try to block opponent 
    char opp = (letter == 'S' ? 'O' : 'S');
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (wouldMakeSOS(b, r, c, opp))
                return { r, c };
        }
    }

    //  Otherwise choose first open space
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (b.get(r, c) == ' ')
                return { r, c };
        }
    }

    return { -1, -1 }; // board full
}
