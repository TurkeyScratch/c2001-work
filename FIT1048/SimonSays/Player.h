/*
 *	author  : James Jefferson Luu
 *	project : Simon Says
 *	purpose : Player Class Header file
 *  created : 2019-11-05
 *  updated : 2019-11-05
 *
 *	This file contains the Player class structure with its member variables 
 *  and function prototypes. It is responsible for holding the Player's
 *  name, total score, best streak, and rank for the program.
 */
#ifndef PLAYER_H
#define PLAYER_H
#include <string>    // required for player name

class Player
{
private:
	std::string playerName;
	int playerScore;
	int playerMaxStreak;
	int playerRank;
public:
	// constructor
	Player();
	Player(std::string newName, int newRank);
	// destructor
	~Player();
	// accessors
	std::string getPlayerName();
	int getPlayerScore();
	int getPlayerMaxStreak();
	int getPlayerRank();
	std::string getPlayerRankName();
	// mutators
	void updatePlayerScore(int newScore);
	void updatePlayerRank(int newRank);
	void updatePlayerMaxStreak(int newStreak);
};
#endif
