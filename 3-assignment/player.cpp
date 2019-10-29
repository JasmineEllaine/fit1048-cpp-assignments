#include <string>
#include <iostream>
#include "player.h"
#include "main.h"

Player::Player() 
{
    playerClass = BABY;
    playerLevel = 1;
    playerTotalPoints = 0;
    setPointsToLevelUp();
    playerCurrentLevelPoints = 0;

    totalWins = 0;
    totalLosses = 0;
    currentWinStreak = 0;
    currentLossStreak = 0;

    pointsEarnedLastMatch = 0;
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

std::string Player::getPlayerClass() {
    if (playerClass == BABY) {
        return "BABY";
    } else if (playerClass == NOVICE) {
        return "NOVICE";
    } else if (playerClass == LEADER) {
        return "LEADER";
    } else if (playerClass == ELITE) {
        return "ELITE";
    } else if (playerClass == CHAMPION) {
        return "CHAMPION";
    } else {
        return "ERROR";
    }
}

int Player:: getPointsToLevelUp() {
    return pointsToLevelUp;
}

void Player::updateWinLossStatistics(bool win) {
    if (win) {
        totalWins++;
        currentWinStreak++;
        currentLossStreak = 0;
    } else {
        totalLosses++;
        currentLossStreak++;
        currentWinStreak = 0;
    }

    // Check if there is a 5 win/loss streak.
    if (currentLossStreak >=5 && playerLevel > 1) {
        levelDown();
        currentLossStreak = 0;
    }

    if (currentWinStreak >= 5) {
        std::string prompt =  "\n\nCongratulations, you're at a 5-game win streak. Do you want to be moved up a level?\nEnter Y or N: ";
        std::string error = "Only input either Y or N: ";
        std::vector<std::string> choices = {"Y", "N"};
        std::string choice = getStringInput(prompt, error, choices);

        if (choice == "Y") {
            levelUp();
            currentWinStreak = 0;
        }
    }
}

// Updates total points and levels up a person if needed.
void Player::updatePointsCounters() {
    playerTotalPoints += pointsEarnedLastMatch;
    int pointsToAdd = pointsEarnedLastMatch;
    while (pointsToAdd != 0) {
        if (pointsToAdd > pointsToLevelUp) {
            int difference = pointsToAdd - pointsToLevelUp;
            pointsToAdd = difference;
            levelUp();
        } else {
            int difference = pointsToLevelUp- pointsToAdd;
            pointsToLevelUp = difference;
            pointsToAdd = 0;
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
    } else if (playerLevel > 6) {
        playerClass = LEADER;
    } else if (playerLevel > 2) {
        playerClass = NOVICE;
    } else if (playerLevel > 0) {
        playerClass = BABY;
    }
}

void Player::displayStats() {
    std::cout << "                     ************************************\n\n                                 PLAYER STATS\n\n                     LEVEL: "
        << playerLevel << "\n                     CLASS: " << getPlayerClass() << "\n\n                     TOTAL POINTS: "
        << playerTotalPoints << "\n                     POINTS UNTIL NEXT LEVEL: "
        << pointsToLevelUp << "\n\n                     TOTAL WINS: "
        << totalWins << "\n                     TOAL LOSSES: " << totalLosses
        << "\n                     TOTAL GAMES PLAYED: "
        << totalLosses+totalWins << "\n\n                     ************************************\n                     Press ENTER to go back to player hub.\n                     ************************************" << std::endl << std::endl;
}