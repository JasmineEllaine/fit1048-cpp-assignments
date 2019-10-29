/*
 * This file is part of 2019 SEM 2 FIT1048 Assignment 3.
 * Created October 2019 by Jasmine Banares, Student ID: 2973 8660.
 */

#include <string>
#include <iostream>
#include <vector>
#include "hackamatch.h"
#include "hackamon.h"
#include "main.h"
#include "player.h"

Hackamon::Hackamon() {
    hackamonState = "IDLE";
}

Hackamon::~Hackamon() {
}

// Getters.
std::vector<std::string> Hackamon::getCommands() {
    /***************************************************************************
     * Returns commands available to player in current state.
     * 
     * @return  commands    Commands available to the player in current state.
     **************************************************************************/
    return commands;
}

Player* Hackamon::getPlayer() {
    /***************************************************************************
     * Returns address where player is stored.
     * 
     * @return  Address of player object.
     **************************************************************************/
    return &player;
}

// Setters.
void Hackamon::setPlayerCommandChoice(std::string choice) {
    /***************************************************************************
     * Sets the command player wants to execute.
     * 
     * @param   choice  Command that the player wants to execute.
     **************************************************************************/
    playerCommandChoice = choice;
}

void Hackamon::runGameIntro() {
    /***************************************************************************
     * Runs the player through the intro scenes and explains the rules.
     **************************************************************************/
    displayTextFromFile("hackamonIntro.txt");

    // Prompt the player for their name and save into player object.
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
    std::cin.get();

    displayTextLineByLine("HackamonBasicRules.txt");
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
        runHackamatch();
    } else if (playerCommandChoice == "SAVE") {
    } else if (playerCommandChoice == "HELP") {
        previousState = hackamonState;
        hackamonState = "HELP";
        if (previousState == "ACTIVE") {
            // Invokes help centre commands until user selects "back" option (5)
            while (hackamonState != "ACTIVE") {
                displayCommands();
                playerCommandChoice = getStringInput("My choice: ",
                                "Sorry, that's not a valid command. Try again: ",
                                commands);
                processPlayerChoice();
            }
        }
    } else if (playerCommandChoice == "EXIT") {
        exitGame = true;
        displayTextFromFile("exitUI.txt");
        std::exit(EXIT_SUCCESS);
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
        player.displayStats();
        pause();
    } else if (playerCommandChoice == "5") {
        std::string tmp = previousState;
        previousState = hackamonState;
        hackamonState = tmp;
    }
}

void Hackamon::runHackamatch() {
    /***************************************************************************
     * Runs a new match for the player.
     **************************************************************************/
    // Select difficulty before starting match.
    int playerLevel = player.getPlayerLevel();

    std::string prompt;
    std::string error = "That's not valid, select again: ";
    std::vector<std::string> choices;
    if (playerLevel < 3) {
        choices = {"EASY"};
        prompt = "Select a difficulty (EASY only): ";
    } else if (playerLevel < 15) {
        choices = {"EASY", "MEDIUM", "HARD"};
        prompt = "Select a difficulty (EASY, MEDIUM, HARD): ";
    } else {
        choices = {"EASY", "MEDIUM", "HARD", "EXTREME"};
        prompt = "Select a difficulty (EASY, MEDIUM, HARD, EXTREME): ";
    }

    std::string difficulty = getStringInput(prompt, error, choices);

    // Start hackamatch.
    previousState = hackamonState;
    hackamonState = "ACTIVE";
    Hackamatch hackamatch = Hackamatch(difficulty, player.getPlayerName(), this);
    hackamatch.run();
    hackamonState = "IDLE";

    // Going back to player hub after hackamatch is over.
    std::cout << "\n\n                     ************************************\n"
        << "                     Press ENTER to go back to player hub.\n"
        << "                     ************************************\n";
    pause();
}

void Hackamon::run(std::string gameStartType) {
    /***************************************************************************
     * Either starts a new game or loads a currently saved game.
     * 
     * @param   gameStartType   Must be either "NEW" or "LOAD".
     **************************************************************************/
    if (gameStartType == "LOAD"){ 
        // ADD CODE HERE FOR IF GAME IS LOADED
        std::cout << "Sorry, I didn't manage to do the save/load feature as I ran out of time. :(";
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