/*
 *	author  : James Jefferson Luu
 *	project : Simon Says
 *	purpose : Dialogue Class Header file
 *  created : 2019-11-05
 *  updated : 2019-11-10
 *
 *	This file contains the functions required for the Dialogue class.
 *  It is responsible for the obtaining and returning
 *  of dialogue strings in Simon Says.
 */
#include "Dialogue.h"    // header file with class structure

 // private functions for constructor
void Dialogue::getDialogueFile(std::string fileName) {
	std::ifstream fileToRead(fileName);
	std::string line;
	if (fileToRead.is_open()) {
		while (getline(fileToRead, line)) {
			dialogueResponses.push_back(new std::string(line));
		}
		fileToRead.close();
	}
	else { throw std::invalid_argument("fileDialogueName is not in directory"); }
}

void Dialogue::getUIFile(std::string fileName) {
	std::ifstream fileToRead(fileName);
	std::string line;
	int i = 0;
	if (fileToRead.is_open()) {
		while (getline(fileToRead, line)) {
			if (i <= 3) { dialogueBorderTop += line + "\n"; }
			else if (i == 4) { dialogueGamePrompt = line + "\n"; }
			else if (i == 5) { dialogueGameOver = line + "\n"; }
			else { dialogueBorderBottom += line + "\n"; }
			i++;
		}
		fileToRead.close();
	}
	else { throw std::invalid_argument("fileUIName is not in directory"); }
}

// default constructor
Dialogue::Dialogue() {
	dialogueBorderTop = "";
	dialogueGamePrompt = "";
	dialogueGameOver = "";
	dialogueBorderBottom = "";
}

// constructor
Dialogue::Dialogue(std::string fileDialogueName, std::string fileUIName) {
	dialogueBorderTop = "";
	dialogueGamePrompt = "";
	dialogueGameOver = "";
	dialogueBorderBottom = "";
	getDialogueFile(fileDialogueName);
	getUIFile(fileUIName);
}

// destructor
Dialogue::~Dialogue() {
	for (size_t j = 0; j < dialogueResponses.size(); j++) {
		delete (dialogueResponses[j]);
	}
	dialogueResponses.clear();
}

// accessors
std::vector<std::string*>* Dialogue::getDialogueResponse() { return &dialogueResponses; }
size_t Dialogue::getDialogueResponseSize() { return dialogueResponses.size(); }

std::string Dialogue::getDialogueResponseLine(int index) {
	return (*dialogueResponses[index]);
}

std::string Dialogue::getDialogueResponseUI(int index) {
	std::stringstream responseUI;
	std::string responseLine;
	std::string promptLine = "";
	int responseLineSpace;
	if (index == -3) { responseLine = "|" + std::string(MAX_LENGTH, ' ') + "|\n"; }
	else if (index == -2) { 
		responseLine = getDialoguePromptOptions();
		promptLine = "\n It was (sequence of indexes): ";
	}
	else if (index == -1) { responseLine = dialogueGameOver; }
	else {
		responseLine = getDialogueResponseLine(index);
		responseLineSpace = MAX_LENGTH - responseLine.size();
		if (responseLineSpace < 0) {
			throw std::invalid_argument("dialogue in dialogue.txt cannot be over 42 letters");
		}
		responseLine.insert(0, "|");
		responseLine.insert(1, std::string(int(responseLineSpace / 2), ' '));
		responseLine.append(std::string(int((responseLineSpace + 2 - 1) / 2), ' '));
		responseLine.append("|\n");
	}
	responseUI << dialogueBorderTop << responseLine << dialogueBorderBottom << promptLine;
	return responseUI.str();
}

std::string Dialogue::getDialoguePromptOptions() {
	std::string responseLine = dialogueGamePrompt;
	std::string indexLine;
	int indexLineSpace;
	responseLine.append("|" + std::string(MAX_LENGTH, ' ') + "|\n");
	for (size_t i = 0; i < dialogueResponses.size(); i++) {
		indexLine = std::to_string(i + 1) + " : " + getDialogueResponseLine(i);
		indexLineSpace = MAX_LENGTH - indexLine.size() - 11;
		indexLine.insert(0, "|" + std::string(11, ' '));
		indexLine.append(std::string(indexLineSpace, ' ') + "|\n");
		responseLine += indexLine;
	}
	return responseLine;
}
