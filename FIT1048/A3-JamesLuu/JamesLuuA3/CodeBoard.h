/**************************************************
  Project: Master Mind (Assignment 3)
   Author: James Luu
  Purpose: Code Board Class Header File
  This file includes the required libaries,
  classes, declarations, and class for the
  Code Board Class File.
**************************************************/
#ifndef CODEBOARD_H		// define code board class identifier if it doesn't exist
#define CODEBOARD_H
// required as CodeBoard is a inherited class, also inherits included libraries
#include "Board.h"
#include "SkillModifiers.h"

/* standard declarations
   (not using namespace std to reduce errors) */
using std::endl;
using std::string;
using std::stringstream;

class CodeBoard : public Board {
private:
	// member variables
	int currentRow;
	int codeRange;
	string hiddenCode;
	// private methods
	void generateCodeRange(int skillLevel);
	void generateCode();
	int determineCorrectLetters(string& tempHiddenCode, string& moveGuess);
	int determineLetterExist(string& tempHiddenCode, string& moveGuess);
public:
	// constructor methods
	CodeBoard();
	CodeBoard(int skillLevel);
	// destructor methods
	~CodeBoard();

	// accessor methods
	string getHiddenCode();
	int getCodeLength();
	int getCurrentRow();
	int getCodeRange();
	bool isCodeSolved();
	// mutator methods
	void updateCodeBoard(string moveGuess);
	void updateCodeHint();
	void revealCode();
	void resetCodeBoard(int skillLevel);
};
#endif // !CODEBOARD_H
