/*
 * This file is part of 2019 SEM 2 FIT1048 Assignment 3.
 * Created October 2019 by Jasmine Banares, Student ID: 2973 8660.
 */

#ifndef HACKAMON_H
#define HACKAMON_H

#include <string>
#include <vector>
#include "player.h"
#include "hackamatch.h"

class Hackamon {
public:
	Hackamon();
	~Hackamon();

    // @brief: Runs the whole game (Hackamon).
    // @param: gameStartType - Must either be NEW or LOAD.
	void run(std::string gameStartType);
    // @brief: Runs the player through the intro scenes.
    void runGameIntro();
    // @brief: Displays available commands in the current hackamonState.
    void displayCommands();
    // @brief: Takes the action that the player requested.
    void processPlayerChoice();
    // @brief: Starts a new match.
    void runHackamatch();

    // Getters and setters.
    std::vector<std::string> getCommands();
    void setPlayerCommandChoice(std::string choice);
    Player* getPlayer();

private:
    // @param: hackamonState can either be
    // "IDLE" - if in player hub.
    // "ACTIVE" - if a hackamatch is ongoing.
    // "HELP" - if in help centre.
	std::string hackamonState;
    // @brief: Stores the last state before the current one.
    std::string previousState;

    // @brief: The player currently playing the game.
    Player player = Player();
    // @brief: Player's current command choice. 
    std::string playerCommandChoice;
    // @brief: Available commands at the moment.
    std::vector<std::string> commands;

    // @brief: States whether to quit the game.
    bool exitGame = false;
};

#endif