/*
 *	author  : James Jefferson Luu
 *	project : Simon Says
 *	purpose : OS Console Header file
 *  created : 2019-11-05
 *  updated : 2019-11-07
 *
 *	This file contains the alternate function prototypes for Windows Command
 *	prompt instructions.
 */
#ifndef OSCONSOLE_H
#define OSCONSOLE_H
#include <iostream>    // required for basic I/O
#include <string>      // required for extra function parameter

void sysOSPause();
void sysOSClear();
void sysOSPauseClear(std::string prePause);
#endif
