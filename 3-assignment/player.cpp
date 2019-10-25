#include <string>
#include "player.h"

Player::Player() {
    Player_Classes playerClass = BABY;
    int playerLevel = 1;
    int playerTotalPoints = 0;
    setPointsToLevelUp();
    // @brief: Points the player currently hold (less than pointsToLevelUp)
    int playerCurrentLevelPoints = 0;

    int totalWins = 0;
    int totalLosses = 0;
    int highestWinStreak = 0;
    int currentWinStreak = 0;
    int currentLossStreak = 0;
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