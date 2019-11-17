/**************************************************
  Project: Master Mind (Assignment 3)
   Author: James Luu
  Purpose: Code Board Class File
  This class contains the member variables related
  to the Master Mind board (e.g. current code,
  placed guesses and their hints).
**************************************************/
#include "CodeBoard.h"	// include class header

// default constructor method
CodeBoard::CodeBoard() {
	currentRow = 0;
	codeRange = 0;
	hiddenCode = "";
}

/* main constructor method
   at skill level 0, 4 slots, with 2 pre-slots for correct
   letters and existing (incorrect position) letters. */
CodeBoard::CodeBoard(int skillLevel) :
	Board(1 + skillLevelRows[skillLevel], 6 + skillLevel) {
	currentRow = 1;
	generateCodeRange(skillLevel);
	generateCode();
}

// destructor method
CodeBoard::~CodeBoard() {}

// private methods
/* calculates code range for constructor and reset methods 
   codeRange is 6 for parameter 0, 8 for 1, 9 for 2 */
void CodeBoard::generateCodeRange(int skillLevel) {
	codeRange = 6;
	if (skillLevel > 0) {
		codeRange += skillLevel + 1;
	}
}

/* purges the previous code and generates a new random code */
void CodeBoard::generateCode() {
	int codeLength = getCodeLength();
	hiddenCode = "";
	for (int element = 0; element < codeLength; element++) {
		hiddenCode += codeLetters[rand() % codeRange];
	}
}

/* sub-methods for updateCodeBoard() to compare guess with copy of hidden code */
int CodeBoard::determineCorrectLetters(string& tempHiddenCode, string& moveGuess) {
	int correctLetters = 0;
	for (int i = 0; i < getCodeLength(); i++) {
		if (moveGuess[i] == tempHiddenCode[i]) {
			moveGuess[i] = '_';
			tempHiddenCode[i] = '_';
			correctLetters++;
		}
	}
	return correctLetters;
}
int CodeBoard::determineLetterExist(string& tempHiddenCode, string& moveGuess) {
	int letterExist = 0;
	size_t found;
	for (int j = 0; j < getCodeLength(); j++) {
		found = tempHiddenCode.find(moveGuess[j]);
		if (found != -1 && moveGuess[j] != tempHiddenCode[j]) {
			tempHiddenCode[found] = '_';
			letterExist++;
		}
	}
	return letterExist;
}

// accessor methods
string CodeBoard::getHiddenCode() { return hiddenCode; }
int CodeBoard::getCodeLength() { return boardNumColumns - 2; }
int CodeBoard::getCurrentRow() { return currentRow; }
int CodeBoard::getCodeRange() { return codeRange; }

bool CodeBoard::isCodeSolved() {
	return getBoardCell(currentRow - 1, 0) == getCodeLength();
}

// mutator methods
/* adds the guess and its clue feedback to the board at current row
   row formatted as [correctLetters, letterExist, guess[0], guess[1]...] */
void CodeBoard::updateCodeBoard(string moveGuess) {
	// parse and compare guess letters
	size_t guessLength = moveGuess.length();
	int correctLetters;
	int letterExist;
	string tempHiddenCode = hiddenCode;
	for (int letter = 0; letter < guessLength; letter++) {
		// insert current letter in respective board position
		updateBoardCell(currentRow, letter + 2, moveGuess[letter]);
	}
	correctLetters = determineCorrectLetters(tempHiddenCode, moveGuess);
	letterExist = determineLetterExist(tempHiddenCode, moveGuess);
	// insert clues (correct pos and wrong pos) in respective position
	updateBoardCell(currentRow, 0, correctLetters);
	updateBoardCell(currentRow, 1, letterExist);
	// go to next row
	currentRow++;
}

/*  reveal a letter in the hidden code */
void CodeBoard::updateCodeHint() {
	int revealLetter = 0;
	// iterates until a new hint is inserted
	do {
		revealLetter = rand() % getCodeLength();
	} while (getBoardCell(0, revealLetter + 2) != 0);
	updateBoardCell(0, revealLetter + 2, hiddenCode[revealLetter]);
}

/* reveals code at the end of the game */
void CodeBoard::revealCode() {
	for (int revealLetter = 0; revealLetter < getCodeLength(); revealLetter++) {
		updateBoardCell(0, revealLetter + 2, hiddenCode[revealLetter]);
	}
}

/* resets the code board (and resizes it if skill level has changed) */
void CodeBoard::resetCodeBoard(int skillLevel) {
	resetBoard(1 + skillLevelRows[skillLevel], 6 + skillLevel);
	currentRow = 1;
	generateCodeRange(skillLevel);
	generateCode();
}