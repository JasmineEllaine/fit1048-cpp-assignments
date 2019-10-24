#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string playerName;
    
public:
	Player();
	~Player();

    // @brief: Returns the players name.
    // @return: The player's name.
    std::string getPlayerName();
    // @brief: Sets the players name.
    void setPlayerName(std::string name);
};

#endif