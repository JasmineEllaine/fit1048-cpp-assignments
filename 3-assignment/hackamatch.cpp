#include <string>
#include <vector>
#include <iostream>
#include "hackamatch.h"
#include "hackamon.h"
#include "main.h"

Hackamatch::Hackamatch(std::string difficulty, std::string name, Hackamon *game) {
    hackamatchDifficulty = difficulty;
    playerName = name;
    game = game;
    
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

    // Initialise playerGuesses and feedback to 2D array with row=numberOfTurns
    // and column = MAX_CODE_LENGTH and all values equal to " ".
    // playerGuesses[numberOfTurns][MAX_CODE_LENGTH];
    // feedback[numberOfTurns][MAX_CODE_LENGTH];
    playerGuesses = new std::string*[numberOfTurns];
    feedback = new std::string*[numberOfTurns];
    for (int i = 0; i < numberOfTurns; i++) {
        playerGuesses[i] = new std::string[MAX_CODE_LENGTH];
        feedback[i] = new std::string[MAX_CODE_LENGTH];
        for (int j = 0; j < MAX_CODE_LENGTH; j++) {
            playerGuesses[i][j] = " ";
            feedback[i][j] = " ";
        }
    }
}

Hackamatch::~Hackamatch() {
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
    std::string prompt = "Do you want to view the rules before we begin?\nInput Y or N: ";
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
            std::string choice = getStringInput("My choice: ",
                            "Sorry, that's not a valid command. Try again: ",
                            game->getCommands());
            game->setPlayerCommandChoice(choice);
            game->processPlayerChoice();
        }
    } while (userChoice != "G");

    // Asks user for their guess.
    std::cout << playerName << ":\> Your guess: ";
    std::cin >> currPlayerGuess;
    while (currPlayerGuess.length() != codeLength) {
        std::cout << "error: guess has incorrect length - remember to input your guess without spaces" << std::endl
            << ":\> Your guess: ";
        std::cin >> currPlayerGuess;
        std::cout << currPlayerGuess;
    }
}

void Hackamatch::getTurnFeedback() {}

void Hackamatch::run() {
    runHackamatchIntro();
    while (turnsLeft > 0) {
        displayUI();
        playUserTurn();
        getTurnFeedback();
        turnsLeft--;
    }
}