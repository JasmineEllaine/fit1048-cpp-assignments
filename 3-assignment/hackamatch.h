/*
 * This file is part of 2019 SEM 2 FIT1048 Assignment 3.
 * Created October 2019 by Jasmine Banares, Student ID: 2973 8660.
 */

#ifndef HACKAMATCH_H
#define HACKAMATCH_H

#include <string>
#include <vector>
#include "player.h"

class Hackamon;

class Hackamatch {
    private:
        // @brief: The overarching Hackamon! game. DONT DELETE HERE.
        Hackamon *game;
        std::string hackamatchDifficulty;
        std::string playerName;
    
        // @brief: Generated passcode to be guessed.
        std::vector<int> passcode;
        // @brief: Passcode on display at the bottom of the UI. Initially equal
        // to '*' unless revealed by the player using HINTS.
        std::string *passcodeDisplay;
        // @brief: Actual length of the passcode to be generated.

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

        // @brief: Tally of player's guesses through the game.
        std::vector<std::vector<std::string>> playerGuesses = {};
        // @brief: Tally of player's feedback throughout the game.
        std::vector<std::vector<std::string>> feedback = {};
        // @brief: The player's latest guess.
        std::vector<int> currPlayerGuess = {};

        // @brief: Current state of the HACKAMATCH. Not to be confused with
        // Hackamoon state.
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