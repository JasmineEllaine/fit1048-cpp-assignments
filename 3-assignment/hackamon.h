#ifndef HACKAMON_H
#define HACKAMON_H

#include <string>

class Hackamon {
public:
	enum hackamonState {
        IDLE,   // Player hub.
		ACTIVE, // During a hackamatch.
		HELP    // Help centre.
	};
    
	Hackamon();
	~Hackamon();

	void run(std::string gameStartType);

private:
	hackamonState state;
};

#endif