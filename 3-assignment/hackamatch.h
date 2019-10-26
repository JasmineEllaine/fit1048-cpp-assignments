#ifndef HACKAMATCH_H
#define HACKAMATCH_H

#include <string>
#include <vector>
class Hackamon;

class Hackamatch {
    private:
        Hackamon *game;
        std::string hackamatchDifficulty;
        std::string playerName;
        std::vector<std::string> passcode;
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
        std::string **playerGuesses;
        std::string **feedback;
        std::string currPlayerGuess = "";
    
    public:
        Hackamatch(std::string difficulty, std::string name, Hackamon *game);
        ~Hackamatch();
        void generatePasscode();
        void run();
        void runHackamatchIntro();
        void displayUI();
        void playUserTurn();
        void getTurnFeedback();
};

#endif