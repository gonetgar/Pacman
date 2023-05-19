#ifndef BOARD 
#define BOARD

#include <iostream>
#include <string>
using namespace std;
#include <fstream>
#include "Operation.h"

class Board
{
	char board[BOARD_HEIGHT][BOARD_WIDTH];
public:
	Board() {}
	//Board(string& file_name);
	void createBoard(ifstream& board_file);
	char getCellItem(int row, int col) { return board[row][col]; }
	void setCellItem(int row, int col, char item) { board[row][col] = item; }
	void printBoard(int* total_breadcrumbs);
};

#endif