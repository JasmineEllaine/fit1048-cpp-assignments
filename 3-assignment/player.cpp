#include <string>
#include "player.h"
#include "main.h"

Player::Player(std::string name) {
    playerName = name;
}

Player::~Player() {
}

std::string Player::getPlayerName() {\
    /***************************************************************************
     * Returns the player's name.
     * 
     * @return  playerName  The player's name.
     **************************************************************************/
    return playerName;
}