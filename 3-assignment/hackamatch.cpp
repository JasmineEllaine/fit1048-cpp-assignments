#include <string>
#include <vector>
#include <iostream>
#include "hackamatch.h"
#include "main.h"

Hackamatch::Hackamatch(std::string difficulty, std::string name) {
    hackamatchDifficulty = difficulty;
    playerName = name;
    
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

    // Initialise passcode to display on the UI to either "*" and " ".
    passcodeDisplay[MAX_CODE_LENGTH];
    for (int i = 0; i < MAX_CODE_LENGTH; i++) {
        if (i < codeLength) {
            passcodeDisplay[i] = "*";
        } else {
            passcodeDisplay[i] = " ";
        }
    }

    // Initialise playerGuesses and feedback to 2D array with row=numberOfTurns
    // and column = MAX_CODE_LENGTH and all values equal to " ".
    playerGuesses[numberOfTurns][MAX_CODE_LENGTH];
    feedback[numberOfTurns][MAX_CODE_LENGTH];
    for (int i = 0; i < numberOfTurns; i++) {
        for (int j = 0; j < MAX_CODE_LENGTH; j++) {
            playerGuesses[i][j] = " ";
            feedback[i][j] = " ";
        }
    }
}

void Hackamatch::generatePasscode() {
    int curr;
    for (int i=0; i < codeLength; i++) {
        // curr in the range 0 to numberOfOptions-1.
        curr = rand() % numberOfOptions;
        passcode.push_back(std::to_string(curr));
    }
};

void Hackamatch::runHackamatchIntro() {
    std::string prompt = "Do you want to view the rules before we begin?\n Input Y or N: ";
    std::string error = "Only input either Y or N: ";
    std::vector<std::string> choices = {"Y", "N"};
    std::string viewRules = getStringInput(prompt, error, choices);

    if (viewRules == "Y") {
        displayTextFromFile("1-hackamatchRules.txt");
        pause();
    } else {
        std::cout << std::endl << std::endl;
    }
}

void Hackamatch::displayUI() {
    // Display top part of UI.
    displayTextFromFile("uiTop.txt");

    // Display guesses and feedback.
    for (int i = 0; i < numberOfTurns; i++) {
        // Display each turn/row.
        std::cout << "           |   |                                         |    |\n           |   |  "
            << i+1 << " :  ";
        // Display player guesses.
        // It is assumed that playerGuesses has been initalised with place
        // holder guesses.
        for (int j = 0; j < MAX_CODE_LENGTH; j++) {
            // Iterate through array of strings.
            // It is assumed that if codeLength < MAX_CODE_LENGTH that the rest
            // of the array is fillef with " ".
            std::cout << playerGuesses[i][j] << " ";
        }
        std::cout << "  ";
        // Display first half of feedback to user. Same assumptions as above.
        for (int j = 0; j < 5; j++) {
            std::cout << playerGuesses[i][j] << " ";
        }
        std::cout << "  |    |\n           |   |                             ";
        // Display second half of feedback to user. Same assumptions as above.
        for (int j = 5; j < MAX_CODE_LENGTH; j++) {
            std::cout << playerGuesses[i][j] << " ";
        }
        std::cout << "  |    |\n";
    }

    // Display the digits that could make up the passcode.
    std::cout << "           |   | _______________________________________ |    |\n"
        << "           |   |                                         |    |\n"
        << "           |   |  ALLOWED DIGITS: ";
    for (int i = 0; i < MAX_CODE_LENGTH; i++) {
        if (i < numberOfOptions) {
            std::cout << i << " ";
        } else {
            std::cout << "  ";
        }
    }

    // Display passcode in asterisks unless revealed by a hint.
    std::cout << "   |    |\n"
    << "           |   | _______________________________________ |    |\n"
    << "           |   |                                         |    |\n"
    << "           |   |  PASSCODE: ";
    for (int i = 0; i < MAX_CODE_LENGTH; i++){ 
        std::cout << passcodeDisplay[i] << " ";
    }

    // Display rest of UI (keyboard).
    std::cout << "         |    |\n"
        << "           |   |_________________________________________|    |\n"
        << "           |                                                  |\n"
        << "            \_________________________________________________/\n"
        << "                   \___________________________________/\n"
        << "                ___________________________________________\n"
        << "             _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- `-_\n"
        << "          _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.`-_\n"
        << "       _-'.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-`__`. .-.-.-.`-_\n"
        << "    _-'.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-----. .-.-.-.-.`-_\n"
        << " _-'.-.-.-.-.-. .---.-. .-------------------------. .-.---. .---.-.-.-.`-_\n"
        << ":-------------------------------------------------------------------------:\n"
        << "`---._.-------------------------------------------------------------._.---'\n\n\n"
        << "––-------------------------------------------------------------------------\n\n";
}

void Hackamatch::playUserTurn() {

}

void Hackamatch::run() {
    runHackamatchIntro();
    while (numberOfTurns > 0) {
        displayUI();
        playUserTurn();
    }
}