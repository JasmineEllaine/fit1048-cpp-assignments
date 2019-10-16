#include <string>
#include <iostream>
#include <vector>
#include "hackamon.h"
#include "main.h"
#include "player.h"

Hackamon::Hackamon() {
    // Setup default hackamon state.
    hackamonState = "IDLE";
}

Hackamon::~Hackamon() {
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
        // Display intro and as for user's name.
        displayTextFromFile("hackamonIntro.txt");

        // Prompt the player for their name.
        std::string name = getStringInput(
            "\nBefore we get started, enter your name: ",
            "Error, try again: ", {""});
        // Create a new player and save their name.
        Player player = Player(name);

        std::cout << player.getPlayerName() << std::endl;
        displayTextLineByLine("HackamonBasicRules.txt");
    }
}