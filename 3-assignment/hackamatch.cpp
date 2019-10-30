/*
 * This file is part of 2019 SEM 2 FIT1048 Assignment 3.
 * Created October 2019 by Jasmine Banares, Student ID: 2973 8660.
 */

#include <iostream>
#include <string>
#include <vector>
#include "hackamatch.h"
#include "hackamon.h"
#include "main.h"
#include "player.h"

Hackamatch::Hackamatch(std::string difficulty, std::string name, Hackamon *hackamon) {
    /***************************************************************************
     * @param   difficulty  Chosen difficulty of the player.
     * @param   name        Player's name.
     * @param   hackamon    The current active hackamon.
     **************************************************************************/
    hackamatchDifficulty = difficulty;
    playerName = name;
    game = hackamon;
    
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
    turnsLeft = numberOfTurns;
    generatePasscode();

    // Initialise passcode to display on the UI to either "*" or " ".
    // IF the length of the passcode generated is only four, then the first four
    // elements of passcodeDisplay will be "*", and the rest are " ". This will
    // be used to make displaying the UI later easier.
    passcodeDisplay = new std::string[MAX_CODE_LENGTH];
    for (int i = 0; i < MAX_CODE_LENGTH; i++) {
        if (i < codeLength) {
            passcodeDisplay[i] = "*";
        } else {
            passcodeDisplay[i] = " ";
        }
    }

    // Initialise playerGuesses and feedback to 2D vector with row=numberOfTurns
    // and column = MAX_CODE_LENGTH and all values equal to " ".
    // playerGuesses[numberOfTurns][MAX_CODE_LENGTH];
    // // feedback[numberOfTurns][MAX_CODE_LENGTH];
    for (int i = 0; i < numberOfTurns; i++) {
        std::vector<std::string> row = {};
        for (int j = 0; j < MAX_CODE_LENGTH; j++) {
            row.push_back(" ");
        }
        playerGuesses.push_back(row);
        feedback.push_back(row);
    }
}

Hackamatch::~Hackamatch() {
    delete[] passcodeDisplay;
}

void Hackamatch::generatePasscode() {
    /***************************************************************************
     * Generates the required passcode and stores it into passcode.
     * passcode.size() = codeLength
     **************************************************************************/
    int curr;
    for (int i=0; i < codeLength; i++) {
        // curr in the range 0 to numberOfOptions-1.
        curr = rand() % numberOfOptions;
        passcode.push_back(curr);
    }
};

void Hackamatch::runHackamatchIntro() {
    /***************************************************************************
     * Runs player through intro scene of a hackamatch. This is where the rules
     * are displayed if needed by the player.
     **************************************************************************/
    std::string prompt = "\nDo you want to view the rules before we begin?\nInput Y or N: ";
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
    /***************************************************************************
     * Displays the board UI, which in this case is a computer.
     **************************************************************************/
    // Display top part of UI.
    displayTextFromFile("uiTop.txt");

    // Display guesses and feedback row by row.
    for (int i = 0; i < numberOfTurns; i++) {
        // Code to display parts of the computer UI.
        std::cout << "           |   |                                         |    |\n           |   |  "
            << i+1;
        if (i+1 < 10) {
            std::cout << " :  ";
        } else {
            std::cout << ":  ";
        }

        // Display player guesses.
        // It is assumed that playerGuesses has been initalised with place
        // holder guesses.
        for (int j = 0; j < MAX_CODE_LENGTH; j++) {
            // Iterate through array of strings.
            // It is assumed that if codeLength < MAX_CODE_LENGTH that the rest
            // of the array is filled with " ".
            std::cout << playerGuesses[i][j] << " ";
        }
        std::cout << "  ";
        // Display first half of feedback to user. Same assumptions as above.
        for (int j = 0; j < 5; j++) {
            std::cout << feedback[i][j] << " ";
        }
        std::cout << "  |    |\n           |   |                             ";
        // Display second half of feedback to user. Same assumptions as above.
        for (int j = 5; j < MAX_CODE_LENGTH; j++) {
            std::cout << feedback[i][j] << " ";
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
    std::cout << "         |    |";
    displayTextFromFile("uiBottom.txt");
}

void Hackamatch::displayHint() {
    /***************************************************************************
     * Reveals one digit of the passcode as chosen by the user.
     **************************************************************************/
    std::string prompt = "\nWhich digit would you like to have revealed? Enter its position below.\n0 = 1st position, 1 = 2nd position etc.\n\nPosition: ";
    int digitIndex = getIntInput(prompt, 0, codeLength-1);

    bool alreadyDisplayed = false;
    while (!alreadyDisplayed) {
        // If digit is = "*", it means it is not yet displayed on the UI, so
        // this needs to be changed to the actual digit.
        if (passcodeDisplay[digitIndex] == "*") {
            alreadyDisplayed = true;
            passcodeDisplay[digitIndex] = std::to_string(passcode[digitIndex]);
            hintsLeft--;
            break;
        }
        std::cout << "That digit has already been revealed try again." << std::endl;
        digitIndex = getIntInput(prompt, 0, codeLength-1);
    }

    displayUI();
}

void Hackamatch::playUserTurn() {
    /***************************************************************************
     * The user's turn:
     *  1. Asks if they want to enter a passcode or a command.
     *  2. Asks for input.
     *  3. Validates input.
     * 
     * Every turn ends after the user has inputted a guess.
     **************************************************************************/
    std::string userChoice;
    do {
        // Ask user if they want to guess the code or enter a command.
        std::cout << "\n\nDo you want to guess the passcode or enter a command (e.g. HINT)?"
            << std::endl;
        std::string prompt = "Write \"G\" for guess or \"C\" for command: ";
        std::string error = "Error. Enter either \"G\" or \"C\" only: ";
        std::vector<std::string> choices = {"G", "C"};
        userChoice = getStringInput(prompt, error, choices);

        if (userChoice == "C") {
            // Commands taken from Hackamon class.
            game->displayCommands();
            std::vector<std::string> commands = game->getCommands();
            std::string choice = getStringInput("My choice: ",
                            "Sorry, that's not a valid command. Try again: ",
                            game->getCommands());             
            game->setPlayerCommandChoice(choice);

            // Process commands differently if hint/forfeit.
            if (choice == "HINT") {
                if (hintsLeft <= 0) {
                    std::cout << "\nSorry, you have used up all of your available hints." << std::endl;
                    continue;
                }
                displayHint();
                continue;
            } else if (choice == "FORFEIT") {
                currentState = "LOSE";
                return;
            }

            // Process commands as per Hackamon class if not HINT/FORFEIT.
            game->processPlayerChoice();
        }
    } while (userChoice != "G");

    // Asks user for their guess.
    std::cout << "\n\nEnter your guesses one digit at a time by entering your guess, then pressing enter." << std::endl;
    int count = 0;
    int guess;
    do {
        std::string prompt = "Digit #" + std::to_string(count+1) + ": ";
        guess = getIntInput(prompt, 0, numberOfOptions-1);
        currPlayerGuess.push_back(guess);
        count++;
    }
    // I only check the length of the player guess because the feedback will
    // deal with any invalid characters as simply a wrong guess.
    while (currPlayerGuess.size() != codeLength);
}

void Hackamatch::getTurnFeedback(std::vector<int> passcodeTemp) {
    /***************************************************************************
     * Processes player's guess and updates player guess and feedback vector\
     * accordingly.
     * 
     * @param   passcodeTemp    Copy of passcode.
     **************************************************************************/
    int turnNo = numberOfTurns - turnsLeft;

    // Counts the number of correct digits and positions.
    int correctDigitAndPos = 0;
    // Counts correct digits only.
    int correctDigitOnly = 0;

    // Iterate through every character of currPlayerGuess to check for digits
    // that are in the correct position.
    for (int i = 0; i < codeLength; i++) {
        // Adds current guess to the playerGuess vector to keep a tally.
        playerGuesses[turnNo][i] = std::to_string(currPlayerGuess[i]);
        	
        // Check if correct position and digit.
        if (passcodeTemp[i] == currPlayerGuess[i]) {
            correctDigitAndPos++;

            // Replace temps with other digits outside of numberOfOptions so
            // that they don't get checked again by feedback.
            passcodeTemp[i] = -1;
            currPlayerGuess[i] = 10;
        }
    }

    // Checks if any remaining digits are correct but in the wrong position.
    for (int i = 0; i < codeLength; i++) {
        // Find currPlayerGuess[i] in passcode.
        std::vector<int>::iterator it = std::find(passcodeTemp.begin(), passcodeTemp.end(), currPlayerGuess[i]);
        	
        // Check if correct position and digit.
        if (it != passcodeTemp.end()) {
            correctDigitOnly++;
            int index = std::distance(passcodeTemp.begin(), it);

            // Replace temps as above.
            currPlayerGuess[i] = 10;
            passcodeTemp[index] = -1;
        }
    }

    // Populate feedback vector with the right amount of "=" and "-".
    int i = 0;
    while (i < correctDigitOnly) {
        feedback[turnNo][i++] = '-';
    }
    int j = 0;
    while (j < correctDigitAndPos) {
        feedback[turnNo][i++] = '=';
        j++;
    }

    // Reset currPlayerGuess
    currPlayerGuess = {};

    // WIN condition = if the number of correct digits = length of passcode.
    if (correctDigitAndPos == codeLength) {
        currentState = "WIN";
    }
}

void Hackamatch::displayGameOverScreen() {
    /***************************************************************************
     * Game over screen displayed at the end of every hackamatch.
     **************************************************************************/
    displayTextFromFile("gameOverUITop.txt");
    std::cout << "             |   |             |   ";

    // Screen displays either YOU WIN or YOU LOSE.
    if (currentState == "WIN") {
        std::cout << "YOU WIN ";
    } else {
        std::cout << "YOU LOSE";
    }
    std::cout << "  |             |    |\n             |   |             +-------------+             |    |\n             |   |                                         |    |\n             |   |   PASSCODE: ";
    
    // Replace '*' in passocdeDisplay to actual passcode, to be revealed to 
    // player.
    for (int i = 0; i < codeLength; i++){ 
        passcodeDisplay[i] = std::to_string(passcode[i]);
    }
    for (int i = 0; i < MAX_CODE_LENGTH; i++){ 
        std::cout << passcodeDisplay[i] << " ";
    }
    std::cout << "        |    |";
    displayTextFromFile("gameOverUIBottom.txt");
}

void Hackamatch::displayResults(int base, int bonus, int penalty, int total, int playerLevel, std::string playerClass, int pointsToLevelUp) {
    /***************************************************************************
     * Displays the numerical results of the hackamatch that just ended, and 
     * some of the player stats.
     * 
     * @param   base    Base points that could be earned in game.
     * @param   bonus   Bonus points the player earned for using less turns.
     * @param   penalty Deductions from using hins.
     * @param   total   Player's new total points earned at Hackamon!
     * @param   playerLevel Player's new level.
     * @param   playerClass Player's new class.
     * @param   pointsToLevelUp Points needed for the player to level up.
     **************************************************************************/
    std::cout << "\n\n                     ************************************\n\n                                 GAME RESULTS\n\n                     BASE POINTS: "
        << base << "\n                     TURNS LEFT BONUS: " << bonus << "\n                     HINT PENALTY: "
        << penalty << "\n\n                     TOTAL POINTS: " << total << "\n\n                     ************************************\n\n                                 PLAYER STATS\n\n                     LEVEL: "
        << playerLevel << "\n                     CLASS: " << playerClass << "\n\n                     POINTS UNTIL NEXT LEVEL: "
        << pointsToLevelUp << std::endl << std::endl;//"\n\n                     ************************************\n                           Press ENTER to continue.\n                     ************************************\n\n";
}

void Hackamatch::updatePlayerStats(Player *player) {
    /***************************************************************************
     * Updates the player's stats accorrding to how this hackamatch went.
     **************************************************************************/
    int points = 0;
    int base = 0;
    int bonus = 0;
    int penalty = 0;

    // Earn points only if player wins.
    if (currentState == "WIN") {
        // Add base points earned.
        if (hackamatchDifficulty == "EASY") {
            base = 200;
        } else if (hackamatchDifficulty == "MEDIUM") {
            base = 300;
        } else if (hackamatchDifficulty == "HARD") {
            base = 500;
        } else if (hackamatchDifficulty == "EXTREME") {
            base = 1000;
            player->winExtremeDifficulty = true; // Unlocks champion class.
        }

        // Bonus points for turnsLeft.
        bonus = (20*turnsLeft);

        // Reduce points for hints.
        penalty = (50*(maxHints-hintsLeft));

        // Calculate points earned.
        points = base + bonus - penalty;
    }

    player->setPointsEarnedLastMatch(points);
    player->updatePointsCounters();

    bool win = (currentState == "WIN") ? true : false;
    player->updateWinLossStatistics(win);

    displayResults(base, bonus, penalty, points, player->getPlayerLevel(), player->getPlayerClass(), player->getPointsToLevelUp());
}

void Hackamatch::run() {
    /***************************************************************************
     * Runs a hackamatch.
     **************************************************************************/
    runHackamatchIntro();

    // Game state will remain active until either: WIN or LOSE.
    while (currentState == "ACTIVE" && turnsLeft > 0) {
        displayUI();
        playUserTurn();
        if (currentState == "ACTIVE") {
            getTurnFeedback(passcode);
        } else {
            continue;
        }
        turnsLeft--;
    }

    // If game state at this point = ACTIVE/LOSE = LOSE game.
    // If game state at this point = WIN = WIN game.
    displayGameOverScreen();
    std::cout << "\n\n                     ************************************\n"
        << "                           Press ENTER to continue.\n"
        << "                     ************************************\n";
    pause();
    updatePlayerStats(game->getPlayer());
}