/*
 *	author  : James Jefferson Luu
 *	project : Simon Says
 *	purpose : Console UI Header file
 *  created : 2019-11-05
 *  updated : 2019-11-07
 *
 *	This file contains the functions related to the console input and output.
 */
#include "ConsoleUI.h"    // header file with libaries and prototypes

/* uses player accessor functions from player pointer to form a stats UI */
std::string getPlayerString(Player* pPlayer) {
	std::stringstream playerStrStream;
	playerStrStream << ":" << std::string(38, '-') << ":\n";
	playerStrStream << "\t Player Name: " << pPlayer->getPlayerName() << "\n";
	playerStrStream << ":" << std::string(38, '-') << ":\n";
	playerStrStream << "\t Player Rank: " << pPlayer->getPlayerRank() << "\n";
	playerStrStream << "\t Total Score: " << pPlayer->getPlayerScore() << "\n";
	playerStrStream << "\t Best Streak: " << pPlayer->getPlayerMaxStreak() << "\n";
	playerStrStream << ":" << std::string(38, '-') << ":\n";
	return playerStrStream.str();
}

/********************************************************************
 *  This function prompts the user to enter a given number with a
 *  message. This number must be inbetween lo and hi.
 *  It will prompt them again if the user enters an invalid input.
 *  Otherwise, the number will be returned to the caller.
 *
 *	@param prompt : aforementioned message
 *	@param lo : lower bound number
 *	@param hi : upper bound number
 *	@return userInt : valid user entered integer
 ********************************************************************/
int getUserInt(std::string prompt, int lo, int hi) {
	// initialise as invalid return integer
	int userInt = lo - 1;
	std::string userInput;
	int negative = 0;
	// iterate until a valid integer is entered
	while (userInt < lo || userInt > hi || std::cin.fail()) {
		// ask for integer
		std::cout << prompt + " ";
		std::cin >> userInput;
		// check if negative
		negative = userInput.front() == '-';
		// confirm no invalid numbers then transfer as integer
		if (userInput.find_first_not_of("1234567890", negative) == -1) {
			userInt = stoi(userInput);
		}
	}
	return userInt;
}

std::string getUserString(std::string prompt, bool numOnly) {
	std::string userInput;
	bool isNum = numOnly;
	do {
		std::cout << prompt + " ";
		std::cin >> userInput;
		isNum = (userInput.find_first_not_of("1234567890") == -1);
	} while (numOnly && !isNum);
	return userInput;
}

/* display a string for a limited amount of time (milliseconds) then clears the screen */
void outputStringWithDuration(std::string output, int limit) {
	auto sleepLimit = std::chrono::system_clock::now() + std::chrono::milliseconds(limit);
	std::cout << output << std::endl;
	std::this_thread::sleep_until(sleepLimit);
	sysOSClear();
}
