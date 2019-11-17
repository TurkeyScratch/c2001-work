/**************************************************
  Project: Master Mind (Assignment 3)
   Author: James Luu
  Purpose: Board Class Header File
  This file includes the required libaries,
  declarations, and class for the
  Board Class File.
**************************************************/
#ifndef BOARD_H			// define player class identifier if it doesn't exist
#define BOARD_H
#include <vector>		// for board format
#include <string>		// for spaces on board
#include <sstream>		// for board UI
#include <algorithm>	// re-filling original board

/* standard declarations
   (not using namespace std to reduce errors) */
using std::vector;
using std::string;
using std::stringstream;
using std::fill;

class Board {
private:
	// ensures board cannot be extended or directly accessed by children
	vector<vector<int>> boardVector;
protected:
	// member variables for inherited classes
	int boardNumRows;
	int boardNumColumns;
public:
	// constructor methods
	Board();
	Board(int rows, int columns);
	// destructor method
	~Board();

	// accessor methods
	int getBoardNumRows();
	int getBoardNumColumns();
	int getBoardCell(int rows, int columns);
	// mutator methods
	void updateBoardCell(int rows, int columns, int item);
	void resetBoard(int rows, int columns);
};
#endif // !BOARD_H
