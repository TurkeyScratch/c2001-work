/*
 *	author  : James Jefferson Luu
 *	project : Simon Says
 *	purpose : Driver file	
 *  created : 2019-11-05
 *  updated : 2019-11-06
 *
 *	This file contains the main() function for the Simon Says game.
 */
#include <string>          // required for output and dialogue
#include <ctime>           // required for randomisation and timing
#include "OSConsole.h"     // required for Console pause and clear
#include "ConsoleUI.h"     // required for Console input and output
#include "Player.h"        // required for Player class
#include "Dialogue.h"      // required for Dialogue class
#include "SimonSays.h"     // required for Simon Says class

int main() {
	outputStringWithDuration("\n\t Hi! ", 1000);
	SimonSays test(new Player("James", 0), new Dialogue("dat/Colours.txt", "dat/UIBorder.txt"));
	test.simonGameLoop();

	sysOSPauseClear("\n\t Goodbye!\n\t ");
	return 0;
}

