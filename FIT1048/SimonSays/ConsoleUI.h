/*
 *	author  : James Jefferson Luu
 *	project : Simon Says
 *	purpose : Console UI Header file
 *  created : 2019-11-05
 *  updated : 2019-11-07
 *
 *	This file contains the function prototypes related to the console input
 *  and output.
 */
#ifndef CONSOLEUI_H
#define CONSOLEUI_H
#include <iostream>       // required for basic I/O
#include <string>         // required for UI strings
#include <sstream>        // required for UI strings
#include <chrono>         // required for displaying for a limited time
#include <thread>         // required for displaying for a limited time
#include "OSConsole.h"    // required for displaying for a limited time
#include "Player.h"       // required for use of Player class

std::string getPlayerString(Player* pPlayer);
int getUserInt(std::string prompt, int lo, int hi);
std::string getUserString(std::string prompt, bool numOnly);
void outputStringWithDuration(std::string output, int limit);
#endif
