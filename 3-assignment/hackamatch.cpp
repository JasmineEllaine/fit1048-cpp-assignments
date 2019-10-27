#include <string>
#include <vector>
#include <iostream>
#include "hackamatch.h"
#include "hackamon.h"
#include "main.h"

Hackamatch::Hackamatch(std::string difficulty, std::string name, Hackamon *hackamon) {
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

    // Initialise passcode to display on the UI to either "*" and " ".
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
}

void Hackamatch::generatePasscode() {
    int curr;
    for (int i=0; i < codeLength; i++) {
        // curr in the range 0 to numberOfOptions-1.
        curr = rand() % numberOfOptions;
        passcode.push_back(curr);
    }
};

void Hackamatch::runHackamatchIntro() {
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
    // Display top part of UI.
    displayTextFromFile("uiTop.txt");

    // Display guesses and feedback.
    for (int i = 0; i < numberOfTurns; i++) {
        // Display each turn/row.
        
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
            // of the array is fillef with " ".
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

void Hackamatch::playUserTurn() {
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
            game->displayCommands();
            std::vector<std::string> commands = game->getCommands();
            std::string choice = getStringInput("My choice: ",
                            "Sorry, that's not a valid command. Try again: ",
                            game->getCommands());
            game->setPlayerCommandChoice(choice);
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

// Updates playerGuesses and feedback.
void Hackamatch::getTurnFeedback(std::vector<int> passcodeTemp) {
    int turnNo = numberOfTurns - turnsLeft;
    // Counts the number of correct digits and positions.
    int correctDigitAndPos = 0;
    // Counts correct digits only.
    int correctDigitOnly = 0;

    // Iterate through every character of currPlayerGuess to check for digits
    // that are in the correct position.
    for (int i = 0; i < codeLength; i++) {
        // Updates playerGuess vector.
        playerGuesses[turnNo][i] = std::to_string(currPlayerGuess[i]);
        	
        // Check if correct position and digit.
        if (passcodeTemp[i] == currPlayerGuess[i]) {
            correctDigitAndPos++;
            passcodeTemp[i] = -1;
            currPlayerGuess[i] = 10;
        }
    }

    for (int i = 0; i < codeLength; i++) {
        // Find currPlayerGuess[i] in passcode.
        std::vector<int>::iterator it = std::find(passcodeTemp.begin(), passcodeTemp.end(), currPlayerGuess[i]);
        	
        // Check if correct position and digit.
        if (it != passcodeTemp.end()) {
            correctDigitOnly++;
            int index = std::distance(passcodeTemp.begin(), it);
            currPlayerGuess[i] = 10;
            passcodeTemp[index] = -1;
        }
    }

    // Update feedback vector.
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
}

void Hackamatch::run() {
    runHackamatchIntro();
    while (turnsLeft > 0) {
        std::cout << passcode[0] << passcode[1] << passcode[2] << passcode[3] << std::endl;
        
        displayUI();
        playUserTurn();
        getTurnFeedback(passcode);
        turnsLeft--;
    }
}