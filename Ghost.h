#ifndef GHOST
#define GHOST

#include <stdlib.h>
#include <time.h>
#include <vector>
#include "Position.h"
#include "Operation.h"
#include "Board.h"
#include "Creature.h"

struct Distance
{
	int val;
	int direction;
};

class Ghost : public Creature
{
	int last_dir;
	char direction;
public:
	Ghost();
	Ghost(int row_, int col_);
	const int getLastDir() const { return last_dir; }
	void setLastDir(int new_direction) { last_dir = new_direction; }

	void printGhost() const;
	int ghostMovement(Board& game_board, vector<Ghost>& other_array, int num_ghosts);
	void move(Board& game_board, vector<Ghost>& other_array, int num_ghosts, int new_row, int new_col, int* moved);
	void moveNR(Board& game_board, vector<Ghost>& other_array, int num_ghosts, int moveDir);
	void moveBest(Board& game_board, vector<Ghost>& other_array, int num_ghosts, const Position& pacPos);
	Position& getNextPosition(int direction);
	void reservePreviousItem(Board& game_board);
};

#endif