/**************************************************
  Project: Master Mind (Assignment 3)
   Author: James Luu
  This class contains the member variables related
  to a generic game board (e.g. rows, columns,
  their items).
**************************************************/
#include "Board.h"		// include class header

// default constructor method
Board::Board() {
	boardNumRows = 0;
	boardNumColumns = 0;
}

// main constructor method
Board::Board(int rows, int columns) { resetBoard(rows, columns); }

// destructor method
Board::~Board() {}

// accessor methods
/* simple methods are one-liners to save space */
int Board::getBoardNumRows() { return boardNumRows; }
int Board::getBoardNumColumns() { return boardNumColumns; }

/* gets a cell of the board, accessor for both children and driver */
int Board::getBoardCell(int rows, int columns) {
	return boardVector[rows][columns];
}

// mutator methods
void Board::updateBoardCell(int rows, int columns, int item) {
	boardVector[rows][columns] = item;
}

/* makes board have row amount of vectors with columns amount of blank spaces */
void Board::resetBoard(int rows, int columns) {
	bool initialBoard = (boardNumRows == NULL && boardNumColumns == NULL);
	bool sameBoard = (boardNumRows == rows && boardNumColumns == columns);
	// reset board on start or if reset parameters are different from current
	if (initialBoard || !sameBoard) {
		// set Board member variables to parameters
		boardNumRows = rows;
		boardNumColumns = columns;

		// clears out previous board
		boardVector.clear();

		// resize previous board to rows amount and fill with blank vectors
		boardVector.resize(boardNumRows, vector<int>(boardNumColumns, 0));
	}
	else {
		// retain the same board if same rows and columns and fill with blanks
		for (int row = 0; row < boardNumRows; row++) {
			fill(boardVector[row].begin(), boardVector[row].end(), 0);
		}
	}
}
