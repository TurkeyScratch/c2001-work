/*
 *	author  : James Jefferson Luu
 *	project : Simon Says
 *	purpose : Simon Says Class Header file
 *  created : 2019-11-06
 *  updated : 2019-11-07
 *
 *	This file contains the Simon Says class structure with its member variables
 *  and function prototypes.
 *  It is responsible for managing a game session of Simon Says.
 */
#ifndef SIMONSAYS_H
#define SIMONSAYS_H
#include <string>         // required for player name
#include <ctime>          // required for randomisation and timing
#include "OSConsole.h"    // required for indirect input and output
#include "ConsoleUI.h"    // required for indirect input and output
#include "Player.h"       // required to use Player functions
#include "Dialogue.h"     // required to use Dialogue functions

class SimonSays {
private:
	Player* simonPlayer;
	Dialogue* simonDialogue;
	static int const MAX_STREAK = 31;
	int simonAnswer[MAX_STREAK];
	int simonStreak;
	int simonMaxResponse;
	// private functions
	void simonSetDialogue();
	std::string simonGetResponse();
	bool simonIsGameOver(std::string playerResponse);
	void simonGameOver();
	int simonGetTimeLimit();
	void simonDisplayDialogue();
public:
	// constructors
	SimonSays();
	SimonSays(Player* pPlayer, Dialogue* pDialogue);
	// destructor
	~SimonSays();
	void simonGameLoop();
	void simonResetGame();
};
#endif
