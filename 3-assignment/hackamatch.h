#ifndef HACKAMATCH_H
#define HACKAMATCH_H

#include <string>
#include <vector>
#include "player.h"
class Hackamon;

class Hackamatch {
    private:
        Hackamon *game;
        std::string hackamatchDifficulty;
        std::string playerName;
        std::vector<int> passcode;
        // Passcode on display bottom of the screen UI.
        std::string *passcodeDisplay;
        int codeLength;
        const int MAX_CODE_LENGTH = 10;
        // @brief: Number of possible digits in passcode. E.g. if
        // numberOfOptions = 5, passcode could be made up of numbers from 0-4
        // (0, 1, 2, 3, 4), for a total of 5 digits.
        int numberOfOptions;
        int numberOfTurns;
        int turnsLeft;
        int maxHints;
        int hintsLeft;
        std::vector<std::vector<std::string>> playerGuesses = {};
        std::vector<std::vector<std::string>> feedback = {};
        std::vector<int> currPlayerGuess = {};

        std::string currentState = "ACTIVE";
    
    public:
        Hackamatch(std::string difficulty, std::string name, Hackamon *game);
        ~Hackamatch();
        void generatePasscode();
        void run();
        void runHackamatchIntro();
        void displayUI();
        void playUserTurn();
        void getTurnFeedback(std::vector<int> passcodeTemp);
        void displayHint();
        void displayGameOverScreen();
        void updatePlayerStats(Player *player);
        void displayResults(int base, int bonus, int penalty, int total, int playerLevel, std::string playerClass, int pointsToLevelUp);
};

#endif