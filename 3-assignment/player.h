#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string playerName;
    
public:
	Player(std::string name);
	~Player();
    void setPlayerName(std::string name);
    std::string getPlayerName();
};

#endif