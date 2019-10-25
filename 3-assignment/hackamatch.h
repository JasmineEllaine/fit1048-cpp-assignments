#ifndef HACKAMATCH_H
#define HACKAMATCH_H

#include <string>
#include <vector>

class Hackamatch {
    private:
        std::string hackamatchDifficulty;
        std::string playerName;
        std::vector<std::string> passcode;
        int codeLength;
        // @brief: Number of possible digits in passcode. E.g. if
        // numberOfOptions = 5, passcode could be made up of numbers from 0-4
        // (0, 1, 2, 3, 4), for a total of 5 digits.
        int numberOfOptions;
        int numberOfTurns;
        int maxHints;
        int hintsLeft;
        std::vector<std::vector<std::string>> playerGuesses;
    
    public:
        Hackamatch(std::string difficulty, std::string name);
        ~Hackamatch();
        void generatePasscode();
        void run();
        void runHackamatchIntro();
        void displayUI();
        void playUserTurn();
};

#endif