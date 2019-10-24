#include <string>
#include <iostream>
#include <vector>
#include "hackamon.h"
#include "main.h"
#include "player.h"

Hackamon::Hackamon() {
    hackamonState = "IDLE";
    // Setup default hackamon state.
    // hackamonState = ;
    // commands = {"START, HELP, SAVE, EXIT"};
}

Hackamon::~Hackamon() {
}

void Hackamon::displayCommands() {
    /***************************************************************************
     * Updates commands available in the current game state, then displays the
     * commands available for use.
     **************************************************************************/
    if (hackamonState == "IDLE") {
        commands = {"START" , "HELP", "SAVE", "EXIT"};
        displayTextFromFile("playerHubCommands.txt");
    } else if (hackamonState == "ACTIVE") {
        commands = {"BACK", "HINT", "HELP", "SAVE", "FORFEIT", "EXIT"};
        displayTextFromFile("hackamatchCommands.txt");
    } else if (hackamonState == "HELP") {
        commands = {"1", "2", "3", "4", "5"};
        displayTextFromFile("helpCentreCommands.txt");
    } else {
        std::cout << "Error: Hackamon state not set." << std::endl;
    }
}

void Hackamon::processPlayerChoice() {
    /***************************************************************************
     * Either starts a new game or loads a currently saved game.
     * 
     * @precondition    Player choice has already been selected and has gone
     *                  through validation checks.
     **************************************************************************/
    if (playerCommandChoice == "START") {
    } else if (playerCommandChoice == "SAVE") {
    } else if (playerCommandChoice == "HELP") {
        previousState = hackamonState;
        hackamonState = "HELP";
    } else if (playerCommandChoice == "EXIT") {
    } else if (playerCommandChoice == "BACK") {
    } else if (playerCommandChoice == "HINT") {
    } else if (playerCommandChoice == "FORFEIT") {
    } else if (playerCommandChoice == "1") {
        displayTextFromFile("1-hackamatchRules.txt");
        pause();
    } else if (playerCommandChoice == "2") {
        displayTextFromFile("2-difficultyInformation.txt");
        pause();
    } else if (playerCommandChoice == "3") {
        displayTextFromFile("3-classesLevelsInfo.txt");
        pause();
    } else if (playerCommandChoice == "4") {
        // Display player stats.
    } else if (playerCommandChoice == "5") {
        hackamonState = previousState;
    }
}

void Hackamon::runGameIntro() {
    /***************************************************************************
     * Runs the player through the intro scenes and explains the rules.
     **************************************************************************/
    // Display intro and as for user's name.
    displayTextFromFile("hackamonIntro.txt");

    // Prompt the player for their name.
    std::string name = getStringInput(
        "\nBefore we get started, enter your name: ",
        "Error, try again: ", {""});
    // Create a new player and save their name.
    player.setPlayerName(name);

    // Give user a personalised intro to hackamon.
    std::cout << std::endl << std::endl << "Press ENTER to move on to the next dialogue."
        << std::endl << std::endl;
    pause();
    std::cout <<  "Hi there " << player.getPlayerName() << ", welcome to Hackamon!" ;
    pause();

    displayTextLineByLine("HackamonBasicRules.txt");
}

void Hackamon::run(std::string gameStartType) {
    /***************************************************************************
     * Either starts a new game or loads a currently saved game.
     * 
     * @param   gameStartType   Must be either "NEW" or "LOAD".
     **************************************************************************/
    if (gameStartType == "LOAD"){ 
        // ADD CODE HERE FOR IF GAME IS LOADED
    } else {
        runGameIntro();
        while (!exitGame) {
            displayCommands();
            playerCommandChoice = getStringInput("My choice: ",
                            "Sorry, that's not a valid command. Try again: ",
                            commands);
            processPlayerChoice();
        }
    }
}