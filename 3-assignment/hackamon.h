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
    std::vector<std::string> displayCommands();
    void runGameIntro();

private:
    // ATRRIBUTES
    // hackamonState can either be
    // "IDLE" - if in player hub.
    // "ACTIVE" - if a hackamatch is ongoing.
    // "HELP" - if in help centre.
	std::string hackamonState;
    std::vector<std::string> commands;
    Player player = Player();
};

#endif