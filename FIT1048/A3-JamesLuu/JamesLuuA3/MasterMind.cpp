/**************************************************
  Project: Master Mind (Assignment 3)
   Author: James Luu
  Purpose: Driver File
  This file holds the main functions to run
  the Master Mind game.
**************************************************/
// setup libraries, classes, variables and prototypes
#include "MasterMind.h"

int main() {
	// seed randoms
	srand(unsigned(time(NULL)));

	// initialise object and feedback pointers
	Player* pGamePlayer = NULL;
	CodeBoard* pGameBoard = NULL;
	vector<string> incorrectFeedback;

	// load feedback from file
	getResponses(&incorrectFeedback, "MasterMindText/MasterMindWrongResponses.txt");

	// display rules and pauses
	displayRules("MasterMindText/MasterMindIntro.txt");
	waitForPlayer(false);
	// set and link class objects
	setMasterMind(&pGamePlayer, &pGameBoard);

	// call main game loop
	playMasterMind(pGamePlayer, pGameBoard, &incorrectFeedback);

	// delete unneeded objects from heap memory
	delete pGamePlayer;
	delete pGameBoard;

	// wait and exit
	waitForPlayer(true);
	return 0;
}

/* loads themed responses from a file */
void getResponses(vector<string>* pResponsesVector, string fileName) {
	// opens fileName and assigns it to fileToRead for input
	ifstream fileToRead(fileName);
	string line;
	if (fileToRead.is_open()) {
		// adds responses
		while (getline(fileToRead, line)) {
			pResponsesVector->push_back(line);
		}
		// closes fileName
		fileToRead.close();
	}
	else {
		cout << "\n Responses file not found!\n";
	}
}

/* generates title string for program */
string stringTitle() {
	stringstream gameTitle;
	gameTitle << string(57, '~') << endl;
	gameTitle << "\t\t    Master Mind : Saw\n";
	gameTitle << string(57, '~') << endl;
	return gameTitle.str();
}

/* displays a rules text file line-by-line */
void displayRules(string fileName) {
	system("cls");
	cout << stringTitle();
	// opens fileName and assigns it to fileToRead for input
	ifstream fileToRead(fileName);
	stringstream fileText;
	string line;

	// check if fileToRead actually exists
	if (fileToRead.is_open()) {
		// print fileName line-by-line
		while (getline(fileToRead, line)) {
			fileText << line << endl;
		}
		// closes fileToRead
		fileToRead.close();
		cout << fileText.str();
	}
	else { cout << "\n Rules file not found!\n"; }
}

/* sets the game's player, board, and code */
void setMasterMind(Player** pPlayer, CodeBoard** pBoard) {
	// initialise variables
	string playerName;
	int playerSkill;
	cout << string(57, '~') << endl;
	// ask for player's name
	playerName = askForString("\n What is your name?", false);
	// restrict to integers 0 to 2
	do {
		playerSkill = askForNumber("\n Select the level of pain (difficulty 0 to 2):");
	} while (playerSkill > 2 || playerSkill < 0);

	*pPlayer = new Player(playerName, playerSkill);
	*pBoard = new CodeBoard(playerSkill);
}

/* main game loop */
void playMasterMind(Player* pPlayer, CodeBoard* pBoard, vector<string>* pIncorrectFeedback) {
	// game session flag
	bool endSession = false;
	// initialize game variables
	string validLetters;
	string validLettersView;
	string inputStr = "";
	int cluesLeft;
	int gameScore;
	// initialize code flag
	bool isCode;

	while (!endSession) {
		// displays initial player stats
		cout << pPlayer->getPlayerDetails(0) << endl;
		// set clues left
		cluesLeft = 3;
		// set valid letters
		setCodeLetters(validLetters, validLettersView, pBoard->getCodeRange());
		// set game flags
		isCode = false;
		// while the game is not over (or not broken by "F" or "Q")
		while (!checkGameOver(pBoard)) {
			// pause previous turns before first game
			waitForPlayer(true);
			// display board and valid elements
			cout << stringTitle() << generateBoardASCII(pPlayer, pBoard) << endl;
			cout << " Valid Letters: " << validLettersView << endl;
			// ask for command
			inputStr = askForString("The combination is (without spaces):", true);

			// determine if command was code guess (same length, valid letters)
			isCode = (inputStr.length() == pBoard->getCodeLength()) && (inputStr.find_first_not_of(validLetters) == -1);
			// forfeit or quit program
			if (inputStr == "F" || inputStr == "Q") {
				endSession = (inputStr == "Q");
				break;
			}
			// read command
			else { readGameCommand(pBoard, inputStr, cluesLeft, isCode); }
			// give feedback if code was incorrect
			if (isCode && !pBoard->isCodeSolved()) {
				cout << " " + (*pIncorrectFeedback)[pBoard->getCurrentRow() - 2] << endl;
			}
		}
		// if not quit - score game, give feedback and ask to play again
		if (!endSession) {
			system("cls");
			// print final board with actual code (regardless if solved)
			pBoard->revealCode();
			cout << stringTitle() << generateBoardASCII(pPlayer, pBoard) << endl;
			// no points for losing
			gameScore = pBoard->isCodeSolved() ? getScore(pPlayer, pBoard, cluesLeft) : 0;
			// feedback post-game and ask to play again
			endSession = gameOver(pPlayer, gameScore);
		}
		/* if decided to play again - check skill, promote or demote 
		   player, and reset the board for next game */
		if (!endSession) {
			determineSkill(pPlayer);
			pBoard->resetCodeBoard(pPlayer->getPlayerSkillNum());
		}
	}
	cout << "\n \"Farewell, " + pPlayer->getPlayerName() + ".\"\n";
}

/* restricts valid letters to certain range and creates a copy with spaces inbetween */
void setCodeLetters(string& validLetters, string& validLettersView, int codeRange) {
	validLetters = string(codeLetters).substr(0, codeRange);
	validLettersView = "";
	for (unsigned int i = 0; i < validLetters.length(); i++) {
		validLettersView += validLetters[i];
		validLettersView += ((i == validLetters.length() - 1) ? "\n" : " ");
	}
}

/* reads a non-termination game command (code guesses, clues, help section) */
void readGameCommand(CodeBoard* pBoard, string inputStr, int& cluesLeft, bool isCode) {
	// if code guess - place on board and give feedback
	if (isCode) { pBoard->updateCodeBoard(inputStr); }
	// easter egg
	else if (inputStr == "ZEP") { pBoard->updateCodeBoard(pBoard->getHiddenCode()); }
	// reveal a letter in the code
	else if (inputStr == "C") { revealClue(pBoard, cluesLeft); }
	// display rules file
	else if (inputStr == "H") { displayRules("MasterMindText/MasterMindIntro.txt"); }
	// invalid inputs
	else { cout << " \"That was not a good use of your time.\"\n"; }
}

/* checks if there are clues left then uses CodeBoard's code hint function */
void revealClue(CodeBoard* pBoard, int& cluesLeft) {
	if (cluesLeft > 0) {
		pBoard->updateCodeHint();
		cout << " A letter will be revealed the next time you see this tablet.\n";
		if (--cluesLeft == 1) { cout << " You have 1 clue left.\n"; }
		else { cout << " You have " << cluesLeft << " clues left.\n"; }
	}
	else { cout << " There are no more clues left to save you.\n"; }
}

bool gameOver(Player* pPlayer, int gameScore) {
	char replayPrompt;
	bool hasWon = gameScore > 0;
	// declare win or loss
	if (hasWon) { cout << " \"Congraulations, you have beaten the game.\"\n\n"; }
	else {
		cout << " Your fate is sealed as the device impales your skull.\n";
		cout << " \"Game Over!\"\n\n";
	}
	// update and display player stats
	pPlayer->updatePlayerPostGame(gameScore, hasWon);
	cout << pPlayer->getPlayerDetails(gameScore) << endl << endl;
	// ask to play again
	replayPrompt = askForLetter("\"Would you like to play another game? (y/n)\"");
	// 'Y' to play again, returns true, else false
	return (replayPrompt != 'Y');
}

/* checks game board class to see if code is solved or ran out of rows */
bool checkGameOver(CodeBoard* pBoard) {
	return pBoard->isCodeSolved() or \
		pBoard->getCurrentRow() == pBoard->getBoardNumRows();
}

/* determines the score for a game session, 
   10 points for each clue left, 20 for each turn left,
   10 for each unique letter on code, multiplied by skillLevel */
int getScore(Player* pPlayer, CodeBoard* pBoard, int cluesLeft) {
	int gameScore = 0;
	gameScore += 10 * cluesLeft;
	gameScore += 20 * (pBoard->getBoardNumRows() - pBoard->getCurrentRow());
	gameScore += 10 * determineComplexity(pBoard->getHiddenCode());
	gameScore *= pPlayer->getPlayerSkillNum() + 1;
	return gameScore;
}

/* determines the complexity of a game's code (by unique letters) */
int determineComplexity(string boardCode) {
	int codeComplexity = 0;
	string countedLetters = "";
	while (!boardCode.empty()) {
		// find last letter of hidden code
		if (countedLetters.find(boardCode.back()) == -1) {
			countedLetters += boardCode.back();
			codeComplexity++;
		}
		// remove last letter of hidden code
		boardCode.pop_back();
	}
	return codeComplexity;
}

/* asks for skill promotion after 5 games won in a row, or demotes
   automatically after 5 games lost in a row */
void determineSkill(Player* pPlayer) {
	int playerSkillLevel = pPlayer->getPlayerSkillNum();
	int playerGamesStreak = pPlayer->getPlayerGamesStreak();
	system("cls");
	cout << stringTitle();
	if (playerGamesStreak >= 5 && playerSkillLevel < 2) {
		char promotePrompt;
		cout << " \"I admire your skills in beating my games, but it seems\n";
		cout << "  that you're used to this type of pain...\"\n\n";
		// ask for promotion
		promotePrompt = askForLetter("\"...would you like some more? (y/n)\"");
		// promote if accepted
		switch (promotePrompt) {
		case 'Y':
			cout << "\n \"Good luck...\"\n";
			pPlayer->updatePlayerSkillLevel(++playerSkillLevel);
			pPlayer->updatePlayerStreak(0);
			break;
		default:
			cout << "\n \"As you wish...\"\n";
		}
	}
	else if (playerGamesStreak <= -5 && playerSkillLevel > 0) {
		cout << " \"To see you being crushed by my game bores me, I am\n";
		cout << "  bringing the pain down a notch.\n";
		cout << " \"Don't see this as an act of mercy.\n";
		pPlayer->updatePlayerSkillLevel(--playerSkillLevel);
		pPlayer->updatePlayerStreak(0);
	}
	else { cout << " \"As you wish...\"\n";	}
}

/* generate a string of the game board in ASCII format */
string generateBoardASCII(Player* pPlayer, CodeBoard* pBoard) {
	// initialize board string variables
	stringstream asciiBoard;
	int skillLevel = pPlayer->getPlayerSkillNum();
	int borderLength = 17;
	// alter board string variables if skill level is higher
	borderLength += 3 * (skillLevel) - (skillLevel > 0);
	string headerEmptySpace = (skillLevel == 2 ? " " : "");
	string endsBorder = "\t\t :" + string(borderLength, '~') + ":\n";

	asciiBoard << endsBorder << "\t\t | " << headerEmptySpace << "Combo | ";
	// clues/actual code header
	for (int j = 2; j < pBoard->getBoardNumColumns(); j++) {
		char element = pBoard->getBoardCell(0, j);
		asciiBoard << (element == 0 ? '_' : element) << " ";
	}
	// code attempt rows
	for (int row = 1; row < pBoard->getBoardNumRows(); row++) {
		asciiBoard << "|\n" << "\t\t :" << string(borderLength, '-') << ":\n";
		asciiBoard << generateBoardASCIIRow(pBoard, skillLevel, row);
	}
	asciiBoard << "|\n" << endsBorder;
	return asciiBoard.str();
}

/* sub-function to generateBoardASCII() for each row */
string generateBoardASCIIRow(CodeBoard* pBoard, int skillLevel, int row) {
	stringstream asciiBoardRow;
	char element;
	int correctLetters = pBoard->getBoardCell(row, 0);
	int letterExists = pBoard->getBoardCell(row, 1);
	int notExist = pBoard->getCodeLength() - (correctLetters + letterExists);
	string codeHint = string(correctLetters, '!') + string(letterExists, '?') + string(notExist, '_');

	asciiBoardRow << "\t\t | " << (skillLevel < 1 ? " " : "") << codeHint << " | ";
	for (int col = 2; col < pBoard->getBoardNumColumns(); col++) {
		element = pBoard->getBoardCell(row, col);
		asciiBoardRow << (element == 0 ? '_' : element) << " ";
	}
	return asciiBoardRow.str();
}

/* asks the user for a phrase response (spaces included) */
string askForString(string question, bool upperCase) {
	// initialise variables
	string userInput = "";
	// loop ensures ENTER key does not skip other calls and return isn't empty
	while (userInput.empty()) {
		cout << " " + question + " ";
		getline(cin, userInput);
		cin.clear();
		cin.ignore(0, '\n');
	}
	if (upperCase) {
		transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
	}
	return userInput;
}

/* asks the user for a single character */
char askForLetter(string question) {
	// initialise variables
	string userInput;
	// iterate until user input is a valid letter
	do {
		userInput = askForString(question, false);
	} while (userInput.length() != 1 or !(isalpha(userInput[0])));
	// return capped character input
	return toupper(userInput[0]);
}

/* asks the user for a positive integer */
int askForNumber(string question) {
	// initialise variables
	string userInput;
	// iterate until user input is a valid integer
	do {
		userInput = askForString(question, false);
	} while (userInput.find_first_not_of("0123456789") != -1);
	// return integer
	return stoi(userInput);
}

/* pauses program until any key is pressed, 
   then clears the screen if parameter is true */
void waitForPlayer(bool clearScreen) {
	cout << "\n\t     ";
	system("pause");
	if (clearScreen) { system("cls"); }
}
