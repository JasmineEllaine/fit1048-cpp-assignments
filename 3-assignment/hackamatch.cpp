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

void Hackamatch::run() {
    runHackamatchIntro();
    while (numberOfTurns > 0) {

    }
}