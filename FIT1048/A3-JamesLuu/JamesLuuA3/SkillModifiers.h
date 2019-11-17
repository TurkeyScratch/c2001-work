/**************************************************
  Project: Master Mind (Assignment 3)
   Author: James Luu
  Purpose: Skill Modifiers Header File
  This file defines the modifiers that determine
  the number of guesses and the range of letters
  allowed in the Code Board class file.
**************************************************/
#ifndef SKILLMODIFIERS_H	// define skill modifiers identifier if it doesn't exist
#define SKILLMODIFIERS_H
// skill level rows needed
const int skillLevelRows[3] = { 10, 13, 15 };
// range of letters that CodeBoard can use
const char codeLetters[9] = { 'R', 'G', 'B', 'Y', 'O', 'P', 'M', 'V', 'W' };
#endif // !SKILLMODIFIERS_H
