#ifndef HACKAMON_H
#define HACKAMON_H

#include <string>
#include <vector>
#include "player.h"

class Hackamon {
public:

    // METHODS
	Hackamon();
	~Hackamon();

    // @brief: Runs the whole game (Hackamon).
    // @param: gaemStartType - Must either be NEW or LOAD.
	void run(std::string gameStartType);
    
    // Runs the player through the intro scenes.
    void runGameIntro();

    // Displays available commands given a current state.
    void displayCommands();


private:
    // ATRRIBUTES

    // hackamonState can either be
    // "IDLE" - if in player hub.
    // "ACTIVE" - if a hackamatch is ongoing.
    // "HELP" - if in help centre.
	std::string hackamonState;

    // Available commands at the moment.
    std::vector<std::string> commands;
    Player player = Player();
    bool exitGame = false;

    // Player's current command choice. 
    std::string playerCommandChoice;
};

#endif