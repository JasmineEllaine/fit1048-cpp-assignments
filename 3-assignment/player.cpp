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

    pointsEarnedLastMatch = 0;
    highScore = 0;
}

Player::~Player() {
}

// SETTERS.
void Player::setPlayerName(std::string name) {
    playerName = name;
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

void Player::setPointsEarnedLastMatch(int pointsEarned) {
    pointsEarnedLastMatch = pointsEarned;
    highScore = pointsEarnedLastMatch > highScore ? pointsEarnedLastMatch : highScore;
}

// GETTERS.
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


void Player::updateWinLossStatistics(bool win) {
    if (win) {
        totalWins++;
        currentWinStreak++;
        highestWinStreak = currentWinStreak > highestWinStreak ? currentWinStreak : highestWinStreak;
        currentLossStreak = 0;
    } else {
        totalLosses++;
        currentLossStreak++;
        currentWinStreak = 0;
    }

    // Check if there is a 5 win/loss streak.

}

// Updates total points and levels up a person if needed.
void Player::updatePointsCounters() {
    playerTotalPoints += pointsEarnedLastMatch;
    int pointsToAdd = pointsEarnedLastMatch;
    while (pointsToAdd != 0) {
        if (pointsToAdd > pointsToLevelUp) {
            int difference = pointsToAdd - pointsToLevelUp;
            levelUp();
        } else {
            int difference = pointsToLevelUp- pointsToAdd;
        }
    }
}

void Player::levelUp() {
    playerLevel++;
    setPointsToLevelUp();
    updateClass();
}

void Player::levelDown() {
    playerLevel++;
    setPointsToLevelUp();
    updateClass();
}

void Player::updateClass() {
    if (playerLevel > 15 && winExtremeDifficulty) {
        playerClass = CHAMPION;
    } else if (playerLevel >11) {
        playerClass = ELITE;
    } else if (playerLevel < 6) {
        playerClass = LEADER;
    } else if (playerLevel < 2) {
        playerClass = NOVICE;
    } else if (playerLevel < 0) {
        playerClass = BABY;
    }
}