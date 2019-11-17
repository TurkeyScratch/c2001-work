/*
 *	author  : James Jefferson Luu
 *	project : Simon Says
 *	purpose : Simon Says Class file
 *  created : 2019-11-06
 *  updated : 2019-11-10
 *
 *	This file contains the functions required for the Simon Says class.
 *  It is responsible for managing a game session of Simon Says.
 */
#include "SimonSays.h"    // header file with class structure

 // default constructor
SimonSays::SimonSays() {
	simonPlayer = NULL;
	simonDialogue = NULL;
	memset(simonAnswer, 0, sizeof(simonAnswer));
	simonStreak = 0;
	simonMaxResponse = 0;
}

// actual constructor
SimonSays::SimonSays(Player* pPlayer, Dialogue* pDialogue) {
	simonPlayer = pPlayer;
	simonDialogue = pDialogue;
	memset(simonAnswer, -1, sizeof(simonAnswer));
	simonStreak = 0;
	simonMaxResponse = 0;
}

// destructor
SimonSays::~SimonSays() {}

// private functions
void SimonSays::simonSetDialogue() {
	int highestIndex = simonDialogue->getDialogueResponseSize();
	simonAnswer[simonStreak] = rand() % highestIndex;
	simonStreak += 1;
	// extend player response
	simonMaxResponse *= 10;
	simonMaxResponse += highestIndex;
}

std::string SimonSays::simonGetResponse() {
	return getUserString(simonDialogue->getDialogueResponseUI(-2), true);
}

bool SimonSays::simonIsGameOver(std::string playerResponse) {
	if (simonStreak == sizeof(simonAnswer) || 
		playerResponse.size() != simonStreak) {
		return true;
	}
	bool notMatch = false;
	for (size_t i = 0; i < playerResponse.size(); i++) {
		notMatch = (int)playerResponse[i] - 49 != simonAnswer[i];
		if (notMatch) { break; }
	}
	return notMatch;
}
void SimonSays::simonGameOver() { sysOSPauseClear(simonDialogue->getDialogueResponseUI(-1)); }

int SimonSays::simonGetTimeLimit() {
	int timeLimit = 20;
	if (simonStreak >= 0 && simonStreak <= 5) {
		timeLimit += 400;
	}
	else if (simonStreak >= 6 && simonStreak <= 13) {
		timeLimit += 300;
	}
	else { timeLimit += 200; }
	return timeLimit;
}
void SimonSays::simonDisplayDialogue() {
	std::string dialogueToDisplay;
	int timeLimit = simonGetTimeLimit();
	for (int i = 0; i < simonStreak; i++) {
		dialogueToDisplay = simonDialogue->getDialogueResponseUI(simonAnswer[i]);
		outputStringWithDuration(dialogueToDisplay, timeLimit);
		outputStringWithDuration(simonDialogue->getDialogueResponseUI(-3), 5);
	}
}

// mutators
void SimonSays::simonGameLoop() {
	// get random seed based on time
	srand(unsigned(time(NULL)));

	std::string playerResponse;
	std::string dialogueToDisplay = "";
	do {
		simonSetDialogue();
		simonDisplayDialogue();
		playerResponse = simonGetResponse();
		sysOSClear();
	} while (!simonIsGameOver(playerResponse));
	simonGameOver();
}

void SimonSays::simonResetGame() {
	simonStreak = 0;
	memset(simonAnswer, -1, sizeof(simonAnswer));
	simonMaxResponse = simonDialogue->getDialogueResponseSize();
}