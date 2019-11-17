/**************************************************
  Project: Master Mind (Assignment 3)
   Author: James Luu
  Purpose: Player Class Header File
  This file includes the required libaries,
  declarations, and class for the
  Player Class File.
**************************************************/
#ifndef PLAYER_H		// define player class identifier if it doesn't exist
#define PLAYER_H
#include <string>		// for names and stats UI
#include <sstream>		// for generating stats UI

/* standard declarations
   (not using namespace std to reduce errors) */
using std::string;
using std::stringstream;

class Player {
private:
	// member variables
	string playerName;
	int playerScore;
	int playerGames;
	int playerGamesWon;
	int playerGamesStreak;
	int playerSkillLevel;
public:
	// constructor methods
	Player();
	Player(string newName, int skillLevel);
	// destructor method
	~Player();

	// accessor methods
	string getPlayerName();
	int getPlayerScore();
	int getPlayerGames();
	int getPlayerGamesWon();
	int getPlayerGamesStreak();
	int getPlayerSkillNum();
	string getPlayerSkillName();
	string getPlayerDetails(int gameScore);
	// mutator methods
	void addPlayerScore(int gameScore);
	void addPlayerGames();
	void addPlayerGamesWon();
	void updatePlayerStreak(int value);
	void updatePlayerSkillLevel(int skillLevel);
	void updatePlayerPostGame(int gameScore, bool hasWon);
};
#endif // !PLAYER_H
