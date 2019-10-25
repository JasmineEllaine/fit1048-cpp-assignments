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

    int totalWins;
    int totalLosses;
    int highestWinStreak;
    int currentWinStreak;
    int currentLossStreak;
    
public:
	Player();
	~Player();

    // @brief: Returns the players name.
    // @return: The player's name.
    std::string getPlayerName();
    // @brief: Sets the players name.
    void setPlayerName(std::string name);
};

#endif