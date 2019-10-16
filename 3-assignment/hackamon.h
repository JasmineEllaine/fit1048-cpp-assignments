#ifndef HACKAMON_H
#define HACKAMON_H

#include <string>

class Hackamon {
public:
    // ATRRIBUTES
    // hackamonState can either be
    // "IDLE" - if in player hub.
    // "ACTIVE" - if a hackamatch is ongoing.
    // "HELP" - if in help centre.
	std::string hackamonState;

    // METHODS
	Hackamon();
	~Hackamon();

    // @brief: Runs the whole game (Hackamon).
    // @param: gaemStartType - Must either be NEW or LOAD.
	void run(std::string gameStartType);

private:
};

#endif