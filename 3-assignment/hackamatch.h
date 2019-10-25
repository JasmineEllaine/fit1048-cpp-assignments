#ifndef HACKAMATCH_H
#define HACKAMATCH_H

#include <string>

class Hackamatch {
    private:
        std::string hackamatchDifficulty;
        std::string passcode;
        int codeLength;
        // @brief: Number of possible digits in passcode. E.g. if
        // numberOfOptions = 5, passcode could be made up of numbers from 0-4
        // (0, 1, 2, 3, 4), for a total of 5 digits.
        int numberOfOptions;
        int numberOfTurns;
        int maxHints;
        int hintsLeft;
    
    public:
        Hackamatch(std::string difficulty);
        ~Hackamatch();
        void generatePasscode();
};

#endif