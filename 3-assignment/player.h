#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string playerName;
    
public:
	Player(std::string name);
	~Player();

    // @brief: Returns the players name.
    // @return: The player's name.
    std::string getPlayerName();
};

#endif