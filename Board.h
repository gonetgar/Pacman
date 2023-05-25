#ifndef BOARD 
#define BOARD

#include <iostream>
#include <string>
using namespace std;
#include <fstream>
#include <vector>
#include "Operation.h"
#include "Position.h"

class Board
{
	char board[BOARD_HEIGHT][BOARD_WIDTH];
	Position pacmanPosition;
	vector<Position> ghostsPositions;

public:
	Board() {}
	//Board(string& file_name);
	void createBoard(ifstream& board_file);
	char getCellItem(int row, int col) { return board[row][col]; }
	void setCellItem(int row, int col, char item) { board[row][col] = item; }
	const Position& getPacmanPosition() { return pacmanPosition; }
	vector<Position>& getghostsPositions() { return ghostsPositions; }
	void setPacmanPosition(Position& new_pos) { pacmanPosition = new_pos; }
	void printBoardAndSaveCreaturesPositions(int* total_breadcrumbs);
};

#endif