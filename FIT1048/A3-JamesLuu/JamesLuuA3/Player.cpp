/**************************************************
  Project: Master Mind (Assignment 3)
   Author: James Luu
  Purpose: Player Class File
  This class contains the member variables related
  to the player (e.g. name, score, wins, and
  skill level), and the member functions to
  access and mutate them, in Master Mind.
**************************************************/
#include "Player.h"		// include class header

// default constructor method
Player::Player() {
	playerName = "Nameless";
	playerScore = 0;
	playerGames = 0;
	playerGamesWon = 0;
	playerGamesStreak = 0;
	playerSkillLevel = 0;
}

// main constructor method
Player::Player(string newName, int skillLevel) {
	playerName = newName;
	playerScore = 0;
	playerGames = 0;
	playerGamesWon = 0;
	playerGamesStreak = 0;
	playerSkillLevel = skillLevel;
}

// destructor method
Player::~Player() {}

// accessor methods
/* simple functions are one-liners to save space */
string Player::getPlayerName() { return playerName; }
int Player::getPlayerScore() { return playerScore; }
int Player::getPlayerGames() { return playerGames; }
int Player::getPlayerGamesWon() { return playerGamesWon; }
int Player::getPlayerGamesStreak() { return playerGamesStreak; }
int Player::getPlayerSkillNum() { return playerSkillLevel; }

/* gets the equivalent name for the player's skill level */
string Player::getPlayerSkillName() {
	switch (playerSkillLevel) {
	case 2:
		return "Guillotine";
	case 1:
		return "Amputator";
	case 0:
		// fall through to default
	default:
		return "Stinger";
	}
}

/* generates the player details in a presentable format */
string Player::getPlayerDetails(int gameScore) {
	string playerBorder = "\t" + string(43, '~');
	stringstream playerDetails;
	playerDetails << playerBorder;
	playerDetails << "\n\t Subject:        " << playerName;
	playerDetails << "\n\t Pain Level:     " << getPlayerSkillName();
	playerDetails << "\n\t Games Played:   " << playerGames;
	playerDetails << "\n\t Times Survived: " << playerGamesWon;
	playerDetails << "\n\t Game Score:     " << gameScore;
	playerDetails << "\n\t Total Score:    " << playerScore;
	playerDetails << "\n" << playerBorder;
	return playerDetails.str();
}

// mutator methods
/* simple functions are one-liners to save space */
void Player::addPlayerScore(int gameScore) { playerScore += gameScore; }
void Player::addPlayerGames() { playerGames++; }
void Player::addPlayerGamesWon() { playerGamesWon++; }
void Player::updatePlayerStreak(int newGamesStreak) { playerGamesStreak = newGamesStreak; }
void Player::updatePlayerSkillLevel(int skillLevel) { playerSkillLevel = skillLevel; }

void Player::updatePlayerPostGame(int gameScore, bool hasWon) {
	addPlayerScore(gameScore);
	addPlayerGames();
	// (reset from negative streak and) increment if won
	if (hasWon) {
		addPlayerGamesWon();
		if (playerGamesStreak < 0) { updatePlayerStreak(1); }
		else { playerGamesStreak++; }
	}
	// (reset from positive streak and) decrement if lost
	else {
		if (playerGamesStreak > 0) { updatePlayerStreak(-1); }
		else { playerGamesStreak--; }
	}
}
