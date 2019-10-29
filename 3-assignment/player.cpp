/*
 * This file is part of 2019 SEM 2 FIT1048 Assignment 3.
 * Created October 2019 by Jasmine Banares, Student ID: 2973 8660.
 */

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
    /***************************************************************************
     * Sets the name of the player
     * 
     * @param   name    Name of the player.
     **************************************************************************/
    playerName = name;
}

void Player::setPointsToLevelUp() {
    /***************************************************************************
     * Determines how many points is needed to level up in a given class.
     **************************************************************************/
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
    /***************************************************************************
     * Sets points earned in the latest match finished.
     * 
     * @param   pointsEarned    Points earned in the last completed/forfetied
     *                          hackamatch.
     **************************************************************************/
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
    /***************************************************************************
     * Returns the player's current level.
     * 
     * @return  The player's level.
     **************************************************************************/
    return playerLevel;
}

std::string Player::getPlayerClass() {
    /***************************************************************************
     * Returns a stringified version of the player's class.
     * 
     * @return  Player's class.
     **************************************************************************/
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
        return "ERROR: Player::getPlayerClass() did not return a value.";
    }
}

int Player:: getPointsToLevelUp() {
    /***************************************************************************
     * Gets the remaining number of points needed for player to level up.
     * 
     * @return Points needed to level up.
     **************************************************************************/
    return pointsToLevelUp;
}

void Player::updateWinLossStatistics(bool win) {
    /***************************************************************************
     * Updates the player's win-loss stats. Also demotes the player a level down
     * if they have a 5 loss streak. Promotes player a level up if 5 win streak
     * (optional).
     * 
     * @param   win     True if player won last match, false otherwise.
     **************************************************************************/
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

void Player::updatePointsCounters() {
    /***************************************************************************
     * Updates players points attributes and levels up a person if needed.
     **************************************************************************/
    playerTotalPoints += pointsEarnedLastMatch;

    // pointsToAdd = points not yet counted towards points needed to level up.
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
    /***************************************************************************
     * Increases a player's level by 1, and updates their class accordingly.
     **************************************************************************/
    playerLevel++;
    setPointsToLevelUp();
    updateClass();
}

void Player::levelDown() {
    /***************************************************************************
     * Decreases a player's level by 1, and updates their class accordingly.
     **************************************************************************/
    playerLevel++;
    setPointsToLevelUp();
    updateClass();
}

void Player::updateClass() {
    /***************************************************************************
     * Updates a player's class according to their level.
     **************************************************************************/
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
    /***************************************************************************
     * Displays the player's stats in a neat UI.
     **************************************************************************/
    std::cout << "                     ************************************\n\n                                 PLAYER STATS\n\n                     LEVEL: "
        << playerLevel << "\n                     CLASS: " << getPlayerClass() << "\n\n                     TOTAL POINTS: "
        << playerTotalPoints << "\n                     POINTS UNTIL NEXT LEVEL: "
        << pointsToLevelUp << "\n\n                     TOTAL WINS: "
        << totalWins << "\n                     TOAL LOSSES: " << totalLosses
        << "\n                     TOTAL GAMES PLAYED: "
        << totalLosses+totalWins << "\n\n                     ************************************\n                     Press ENTER to go back to player hub.\n                     ************************************" << std::endl << std::endl;
}