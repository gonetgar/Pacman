#ifndef GHOST
#define GHOST

#include <stdlib.h>
#include <time.h>
#include <vector>
#include "Position.h"
#include "Operation.h"
#include "Board.h"
#include "Creature.h"

struct Distance {
	int val;
	int direction;
};

class Ghost : public Creature
{
	//Position current_position;
	//Position prev_pos;
	int last_dir;
	char direction;
public:
	Ghost();
	Ghost(int row_, int col_);
	//Position& getCurrentPosition() { return current_position; }
	//void setCurrentPosition(int row, int col) { current_position.setRow(row); current_position.setCol(col); }
	//void setCurrentPositionNEWFUNC(Position& new_pos) { current_position = new_pos; }
	int getLastDir() { return last_dir; }
	void setLastDir(int new_direction) { last_dir = new_direction; }

	void printGhost();
	//void ghostMovement(Board& game_board, vector<Ghost>& other_array, int num_ghosts); // , Ghost& other);
	int ghostMovement(Board& game_board, vector<Ghost>& other_array, int num_ghosts);
	//void move(Board& game_board, vector<Ghost>& other_array, int num_ghosts, int new_row, int new_col, int* moved);
	void move(Board& game_board, vector<Ghost>& other_array, int num_ghosts, int new_row, int new_col, int* moved);
	void moveNR(Board& game_board, vector<Ghost>& other_array, int num_ghosts, int moveDir);
	void moveBest(Board& game_board, vector<Ghost>& other_array, int num_ghosts, Position& pacPos);
	int getBestDirection(Board& game_board, vector<Ghost>& other_array, int num_ghosts, Position& pacPos);
	Position& getNextPosition(int direction);
	void reservePreviousItem(Board& game_board);
};

#endif