/**************************************************
  Project: Master Mind (Assignment 3)
   Author: James Luu
  Purpose: Driver Header File
  This file includes the required libaries,
  classes, declarations, and prototypes for the
  Driver File.
**************************************************/
#ifndef MASTERMIND_H	// define application identifier if not defined
#define MASTERMIND_H
#include <iostream>		// for input and output
#include <fstream>		// for file reading 
#include <string>		// for UI and input
#include <ctime>		// for randomisation by time
#include <algorithm>	// for upper case inputs

// include classes
#include "Player.h"
#include "CodeBoard.h"
#include "SkillModifiers.h"

/* standard declarations
   (not using namespace std to reduce errors) */
using std::cin;
using std::cout;
using std::transform;
using std::endl;
using std::getline;
using std::string;
using std::ifstream;
using std::stringstream;

// prototype functions
void getResponses(vector<string>* pResponsesVector, string fileName);
string stringTitle();
void displayRules(string fileName);
void setMasterMind(Player** pPlayer, CodeBoard** pBoard);
void playMasterMind(Player* pPlayer, CodeBoard* pBoard, vector<string>* pIncorrectFeedback);
void setCodeLetters(string& validLetters, string& validLettersView, int codeRange);
void readGameCommand(CodeBoard* pBoard, string inputStr, int& cluesLeft, bool isCode);
void revealClue(CodeBoard* pBoard, int& cluesLeft);
bool gameOver(Player* pPlayer, int gameScore);
bool checkGameOver(CodeBoard* pBoard);
int getScore(Player* pPlayer, CodeBoard* pBoard, int cluesLeft);
int determineComplexity(string boardCode);
void determineSkill(Player* pPlayer);
string generateBoardASCII(Player* pPlayer, CodeBoard* pBoard);
string generateBoardASCIIRow(CodeBoard* pBoard, int skillLevel, int row);

string askForString(string question, bool upperCase);
char askForLetter(string question);
int askForNumber(string question);
void waitForPlayer(bool clearScreen);

#endif // !MASTERMIND_H
