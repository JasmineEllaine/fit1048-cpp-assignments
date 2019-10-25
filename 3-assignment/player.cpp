#include <string>
#include "player.h"

Player::Player() 
{
    playerClass = BABY;
    playerLevel = 1;
    playerTotalPoints = 0;
    setPointsToLevelUp();
    playerCurrentLevelPoints = 0;

    totalWins = 0;
    totalLosses = 0;
    highestWinStreak = 0;
    currentWinStreak = 0;
    currentLossStreak = 0;
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

int Player::getPlayerLevel() {
    return playerLevel;
}

void Player::setPointsToLevelUp() {
    switch (playerClass) {
        case BABY:
            pointsToLevelUp = 500;
            break;
        case NOVICE:
            pointsToLevelUp = 500;
            break;
        case LEADER:
            pointsToLevelUp = 1000;
            break;
        case ELITE:
            pointsToLevelUp = 1500;
            break;
        case CHAMPION:
            pointsToLevelUp = 2000;
            break;
    }
}