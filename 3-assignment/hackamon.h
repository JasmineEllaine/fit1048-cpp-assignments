#ifndef HACKAMON_H
#define HACKAMON_H

#include <string>
#include <vector>
#include "player.h"
#include "hackamatch.h"

class Hackamon {
public:

    // METHODS
	Hackamon();
	~Hackamon();

    // @brief: Runs the whole game (Hackamon).
    // @param: gaemStartType - Must either be NEW or LOAD.
	void run(std::string gameStartType);
    // @brief: Runs the player through the intro scenes.
    void runGameIntro();
    // @brief: Displays available commands given a current state.
    void displayCommands();
    // @brief: Takes the action that the player requested.
    void processPlayerChoice();
    // @brief: Starts a new match.
    void runHackamatch();

private:
    // ATRRIBUTES

    // @brief: hackamonState can either be
    // "IDLE" - if in player hub.
    // "ACTIVE" - if a hackamatch is ongoing.
    // "HELP" - if in help centre.
	std::string hackamonState;
    // @brief: Stores the last state before the current one.
    std::string previousState;

    // @brief: The current hackamatch.
    Hackamatch *hackamatch;

    // @brief: Details of the player currently playing the game.
    Player player = Player();
    // @brief: Player's current command choice. 
    std::string playerCommandChoice;
    // @brief: Available commands at the moment.
    std::vector<std::string> commands;
    // @brief: States whether to quit the game.
    bool exitGame = false;
};

#endif