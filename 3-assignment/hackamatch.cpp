#include <string>
#include "hackamatch.h"

Hackamatch::Hackamatch(std::string difficulty) {
    hackamatchDifficulty = difficulty;
    
    // Setup depending on game difficulty.
    if (difficulty == "EASY") {
        codeLength = 4;
        numberOfOptions = 4;
        numberOfTurns = 10;
    } else if (difficulty == "MEDIUM") {
        codeLength = 6;
        numberOfOptions = 8;
        numberOfTurns = 15;
    } else if (difficulty == "HARD") {
        codeLength = 8;
        numberOfOptions = 10;
        numberOfTurns = 20;
    } else if (difficulty == "EXTREME") {
        codeLength = 10;
        numberOfOptions = 10;
        numberOfTurns = 20;
    }
    maxHints = codeLength - 1;
    hintsLeft = maxHints;

    generatePasscode();
}

void Hackamatch::generatePasscode() {

};