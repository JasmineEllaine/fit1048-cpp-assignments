#include <string>
#include "player.h"

Player::Player() {
}

Player::~Player() {
}

void Player::setPlayerName(std::string name) {
    playerName = name;
}

std::string Player::getPlayerName() {
    /***************************************************************************
     * Returns the player's name.
     * 
     * @return  playerName  The player's name.
     **************************************************************************/
    return playerName;
}