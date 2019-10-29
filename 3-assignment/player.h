/*
 * This file is part of 2019 SEM 2 FIT1048 Assignment 3.
 * Created October 2019 by Jasmine Banares, Student ID: 2973 8660.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string playerName;

    enum Player_Classes {
        BABY,
        NOVICE,
        LEADER,
        ELITE,
        CHAMPION
    };

    Player_Classes playerClass;
    int playerLevel;

    // @brief: Total number of points player has.
    int playerTotalPoints;
    // @brief: Points required for player to level up in current level.
    // BABY/NOVICE = 500 points
    // LEADER = 1000 points
    // ELITE = 1500 points
    // CHAMPION = 2000 points
    int pointsToLevelUp;
    // @brief: Points the player currently hold (less than pointsToLevelUp)
    int playerCurrentLevelPoints;
    // @brief: Points the player earned in their last game.
    int pointsEarnedLastMatch;

    int totalWins;
    int totalLosses;
    // @brief: currentWinStreak and currentLossStreak resets every 5 wins/losses.
    int currentWinStreak;
    int currentLossStreak;
    
public:
	Player();
	~Player();

    // Getters.
    std::string getPlayerName();
    int getPlayerLevel();
    std::string getPlayerClass();
    int getPointsToLevelUp();

    // Setters.
    void setPlayerName(std::string name);
    void setPointsToLevelUp();
    void setPointsEarnedLastMatch(int pointsEarned);

    void updateWinLossStatistics(bool win);
    void updatePointsCounters();

    void levelUp();
    void levelDown();
    void updateClass();

    void displayStats();

    // @brief: Determines if player can move up to champion class,
    bool winExtremeDifficulty = false;
};

#endif