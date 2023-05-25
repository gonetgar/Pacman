// This class presents the creatures possible in the game: ghosts and fruits.

#ifndef CREATURE 
#define CREATURE

#include "Position.h"

class Creature
{
protected:
	Position current_position;
	Position prev_pos;

public:
	Creature() {}

	Position& getCurrentPosition() { return current_position; }
	void setCurrentPosition(int row, int col) { current_position.setRow(row); current_position.setCol(col); }
	void setCurrentPosition(Position new_pos) { current_position = new_pos; }
	Position& getPrevPosition() { return prev_pos; }
	void setPrevPosition(int row, int col) { prev_pos.setRow(row); prev_pos.setCol(col); }
};

#endif
