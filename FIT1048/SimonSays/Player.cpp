/*
 *	author  : James Jefferson Luu
 *	project : Simon Says
 *	purpose : Player Class file
 *  created : 2019-11-05
 *  updated : 2019-11-05
 *
 *	This file contains the functions required for the Player class. 
 *  It is responsible for holding the Player's name, total score,
 *  best streak, and rank for the program.
 */
#include "Player.h"    // header file with class structure

// default constructor
Player::Player() {
	playerName = "Quote";
	playerScore = 0;
	playerMaxStreak = 0;
	playerRank = 0;
}

// constructor
Player::Player(std::string newName, int newRank) {
	playerName = newName;
	playerScore = 0;
	playerMaxStreak = 0;
	playerRank = newRank;
}

// destructor
Player::~Player() {}

/* accessors for each member variable */
std::string Player::getPlayerName() { return playerName;  }
int Player::getPlayerScore() { return playerScore; }
int Player::getPlayerMaxStreak() { return playerMaxStreak; }
int Player::getPlayerRank() { return playerRank; }

/* returns the name equivalent to the rank enum member variable */
std::string Player::getPlayerRankName() { return ""; }

/* mutators for score member variable */
void Player::updatePlayerScore(int newScore) { playerScore += newScore; }

/* overwrites rank member variable */
void Player::updatePlayerRank(int newRank) { playerRank = newRank; }

/* overwrites old max streak member variable if the new streak is higher */
void Player::updatePlayerMaxStreak(int newStreak) { 
	playerMaxStreak = newStreak > playerMaxStreak ? newStreak : playerMaxStreak;
}