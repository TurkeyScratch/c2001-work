/*
 *	author  : James Jefferson Luu
 *	project : Simon Says
 *	purpose : Dialogue Class Header file
 *  created : 2019-11-05
 *  updated : 2019-11-10
 *
 *	This file contains the Dialogue class structure with its member variables
 *  and function prototypes. It is responsible for the obtaining and returning
 *  of dialogue strings in Simon Says.
 */
#ifndef DIALOGUE_H
#define DIALOGUE_H
#include <fstream>    // required for reading a file
#include <string>     // required for dialogue
#include <sstream>    // required for dialogue
#include <vector>     // required for holding the dialogue lists 

class Dialogue
{
private:
	std::vector<std::string*> dialogueResponses;
	std::string dialogueBorderTop;
	std::string dialogueGamePrompt;
	std::string dialogueGameOver;
	std::string dialogueBorderBottom;
	static int const MAX_LENGTH = 42;
	// private function for constructor
	void getDialogueFile(std::string fileName);
	void getUIFile(std::string fileName);
	// private function for accessor
	std::string getDialoguePromptOptions();
public:
	// constructors
	Dialogue();
	Dialogue(std::string fileDialogueName, std::string fileUIName);
	// destructor
	~Dialogue();
	// accessors
	std::vector<std::string*>* getDialogueResponse();
	size_t getDialogueResponseSize();
	std::string getDialogueResponseLine(int index);
	std::string getDialogueResponseUI(int index);
};
#endif
