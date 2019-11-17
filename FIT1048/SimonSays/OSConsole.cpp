/*
 *	author  : James Jefferson Luu
 *	project : Simon Says
 *	purpose : OS Console file
 *  created : 2019-11-05
 *  updated : 2019-11-05
 *	
 *	This file contains the alternate functions for Windows Command
 *	prompt commands.
 */
#include "OSConsole.h"    // header file with libaries and prototypes

/********************************************************************
	This function pauses the program and asks the user to press the
	enter key to continue running. Alternative to "system("pause")"
	for other operating systems.
*********************************************************************/
void sysOSPause() {
	#if defined _WIN32
		system("pause");
	#else
		std::cout << "Press ENTER to continue . . .";
		std::cin.get();
	#endif
}

/********************************************************************
	This function clears the program console. Alternative to
	"system("cls")"	for other operating systems.
*********************************************************************/
void sysOSClear() {
	#if defined _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

/********************************************************************
	This function displays a preliminary message before pausing, 
	then clearing the console.

	@param prePause : aforementioned preliminary message
*********************************************************************/
void sysOSPauseClear(std::string prePause) {
	std::cout << prePause << std::endl;
	sysOSPause();
	sysOSClear();
}
