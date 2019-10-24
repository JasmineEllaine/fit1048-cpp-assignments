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
        commands = {"HINT", "HELP", "SAVE", "FORFEIT", "EXIT"};
        displayTextFromFile("hackamatchCommands.txt");
    } else if (hackamonState == "HELP") {
        commands = {"1", "2", "3", "4", "5", "6"};
        displayTextFromFile("helpCentreCommands.txt");
    } else {
        std::cout << "Error: Hackamon state not set." << std::endl;
    }
}

void Hackamon::runGameIntro() {
    // Display intro and as for user's name.
    displayTextFromFile("hackamonIntro.txt");

    // Prompt the player for their name.
    std::string name = getStringInput(
        "\nBefore we get started, enter your name: ",
        "Error, try again: ", {""});
    // Create a new player and save their name.
    player.setPlayerName(name);

    // Give user a personalised intro to hackamon.
    std::cout << std::endl << std::endl << "Hi there " << player.getPlayerName()
        << ", welcome to Hackamon!" << std::endl << std::endl;
    std::cin.get();
    std::cout << "Press ENTER to move on to the next dialogue.";
    std::cin.get();

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
            std::cout << playerCommandChoice;
        }
    }
}