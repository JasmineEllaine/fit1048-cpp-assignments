#include <string>
#include <iostream>
#include <vector>
#include "hackamon.h"
#include "main.h"
#include "player.h"

Hackamon::Hackamon() {
    state = IDLE;
}

Hackamon::~Hackamon() {
}

void Hackamon::run(std::string gameStartType) {
    if (gameStartType == "LOAD"){ 
        // ADD CODE HERE FOR IF GAME IS LOADED
    } else {
        // Starts a new game by setting state to IDLE.
        state = IDLE;
        // Display intro and as for user's name.
        displayTextFromFile("hackamonIntro.txt");

        // Create a new player and save their name.
        // Player player = Player();
        std::string name = getStringInput(
            "\nBefore we get started, enter your name: ",
            "Error, try again: ", {""});

        // player.setPlayerName(name);
        // std::cout << player.getPlayerName() << std::endl;
    }
}