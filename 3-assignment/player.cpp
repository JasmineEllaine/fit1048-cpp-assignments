#include <string>
#include "player.h"

Player::Player(std::string name) {
    playerName = name;
}

Player::~Player() {
}

void Player::setPlayerName(std::string name) {
    playerName = name;
}

std::string Player::getPlayerName() {
    return playerName;
}