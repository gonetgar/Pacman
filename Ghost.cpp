#include "Ghost.h"

Ghost::Ghost()
{
	// set starting position at (0,0)
	this->current_position.setRow(0);
	this->current_position.setCol(0);
	this->direction = 's'; // starting as "stay"
	this->last_dir = 0;
}

Ghost::Ghost(int row_, int col_)
{
	// set starting position
	this->current_position.setRow(row_);
	this->current_position.setCol(col_);
	this->direction = 's';
	this->last_dir = 0;
}

void Ghost::printGhost()
{
	gotoxy(this->current_position.getCol(), this->current_position.getRow());
	cout << (char)GHOST_PRINT;
}

// places the ghost at random place on the board
//void Ghost::ghostMovement(Board& game_board, vector<Ghost>& other_array, int num_ghosts) //, Ghost& other)
//{
//	srand(time(NULL));
//	int moved = 0;
//
//	while (moved == 0)
//	{
//		int moveDir = (rand() % (4)) + 1;
//		int curRow = this->current_position.getRow();
//		int curCol = this->current_position.getCol();
//
//		switch (moveDir)
//		{
//		case GHOST_UP:
//			this->move(game_board, other_array, num_ghosts, curRow - 1, curCol, &moved);
//			break;
//		case GHOST_DOWN:
//			this->move(game_board, other_array, num_ghosts, curRow + 1, curCol, &moved);
//			break;
//		case GHOST_RIGHT:
//			this->move(game_board, other_array, num_ghosts, curRow, curCol + 1, &moved);
//			break;
//		case GHOST_LEFT:
//			this->move(game_board, other_array, num_ghosts, curRow, curCol - 1, &moved);
//			break;
//		}
//	}
//}

//void Ghost::move(Board& game_board, vector<Ghost>& other_array, int num_ghosts, int new_row, int new_col, int* moved)
//{
//	Position new_pos(new_row, new_col);
//
//	// check if the next position is available
//	char new_position_on_board = game_board.getCellItem(new_row, new_col);
//	bool collision = false; // check if 2 ghosts are collisioning :-)
//
//	for (int i = 0; i < num_ghosts; i++)
//	{
//		if (new_pos == other_array[i].current_position)
//			collision = true;
//	}
//
//	if (new_position_on_board != WALL && new_position_on_board != SIDE_TUNNEL && new_position_on_board != UP_DOWN_TUNNEL && collision == false)
//	{
//		this->reservePreviousItem(game_board);
//		this->current_position.setRow(new_row);
//		this->current_position.setCol(new_col);
//		this->printGhost();
//		*moved = 1;
//	}
//}

////////////////////////////////////////

// places the ghost at random place on the board
///////////////
int Ghost::ghostMovement(Board& game_board, vector<Ghost>& other_array, int num_ghosts)   ///random movement - for Novice
{
	srand(time(NULL));
	int moved = 0, moveDir;

	while (moved == 0)
	{
		moveDir = (rand() % (4)) + 1;
		int curRow = this->current_position.getRow();
		int curCol = this->current_position.getCol();

		switch (moveDir)
		{
		case GHOST_UP:
			this->move(game_board, other_array, num_ghosts, curRow - 1, curCol, &moved);
			break;
		case GHOST_DOWN:
			this->move(game_board, other_array, num_ghosts, curRow + 1, curCol, &moved);
			break;
		case GHOST_RIGHT:
			this->move(game_board, other_array, num_ghosts, curRow, curCol + 1, &moved);
			break;
		case GHOST_LEFT:
			this->move(game_board, other_array, num_ghosts, curRow, curCol - 1, &moved);
			break;
		}
	}

	return moveDir;
}

void Ghost::move(Board& game_board, vector<Ghost>& other_array, int num_ghosts, int new_row, int new_col, int* moved)     /// the actual movement
{
	Position new_pos(new_row, new_col);

	// check if the next position is available
	char new_position_on_board = game_board.getCellItem(new_row, new_col);
	bool collision = false; // check if 2 ghosts are collisioning 🙂

	for (int i = 0; i < num_ghosts; i++)
	{
		if (new_pos == other_array[i].current_position)
			collision = true;
	}

	if (new_position_on_board != WALL && new_position_on_board != SIDE_TUNNEL && new_position_on_board != UP_DOWN_TUNNEL && collision == false)
	{
		this->reservePreviousItem(game_board);
		this->current_position.setRow(new_row);
		this->current_position.setCol(new_col);
		this->printGhost();
		*moved = 1;
	}
}


//void Ghost::moveNR(Board& game_board, vector<Ghost>& other_array, int num_ghosts, int new_row, int new_col, int moveDir)   ///Novice level - no random
void Ghost::moveNR(Board& game_board, vector<Ghost>& other_array, int num_ghosts, int moveDir)   ///Novice level - no random
{
	//int new_row = new_pos.getRow();
	//int new_col = new_pos.getCol();

	int moved = 0;
	int curRow = this->current_position.getRow();
	int curCol = this->current_position.getCol();
	switch (moveDir)
	{
	case GHOST_UP:
		this->move(game_board, other_array, num_ghosts, curRow - 1, curCol, &moved);
		break;
	case GHOST_DOWN:
		this->move(game_board, other_array, num_ghosts, curRow + 1, curCol, &moved);
		break;
	case GHOST_RIGHT:
		this->move(game_board, other_array, num_ghosts, curRow, curCol + 1, &moved);
		break;
	case GHOST_LEFT:
		this->move(game_board, other_array, num_ghosts, curRow, curCol - 1, &moved);
		break;
	}

	if (moved == 0)   //// maybe unacecary, but just to chack in case of collison if it stays, othewise send same c & r
		return;
}


void Ghost::moveBest(Board& game_board, vector<Ghost>& other_array, int num_ghosts, Position pacPos)     /// for best - helper
{

	int moved = 0;
	int curRow = this->current_position.getRow();
	int curCol = this->current_position.getCol();
	int pac_row = pacPos.getRow();
	int pac_col = pacPos.getCol();


		if (curRow < pac_row)
		{
			this->move(game_board, other_array, num_ghosts, curRow + 1, curCol, &moved);
			if (moved == 1)
				return;
		}
	if (curRow > pac_row)
	{
		this->move(game_board, other_array, num_ghosts, curRow - 1, curCol, &moved);
		if (moved == 1)
			return;
	}

	if (curCol < pac_col) {
		this->move(game_board, other_array, num_ghosts, curRow, curCol + 1, &moved);
		if (moved == 1)
			return;
	}
	if (curCol > pac_col) {
		this->move(game_board, other_array, num_ghosts, curRow, curCol - 1, &moved);
		if (moved == 1)
			return;
	}

	////maybe add stay, to check later(in case both equals? not sure if possible)
}

/////////////////////


// sets the previous item on the board before the ghost moved
void Ghost::reservePreviousItem(Board& game_board)
{
	this->prev_pos = this->current_position; // save the current position so that we can go back to it
	int prevRow = this->prev_pos.getRow();
	int prevCol = this->prev_pos.getCol();
	char prev_item_on_board = game_board.getCellItem(prevRow, prevCol);

	// print the previous item that was on the board
	if (prev_item_on_board == BREADCRUMB)
	{
		gotoxy(prevCol, prevRow);
		cout << (char)BREADCRUMB;
	}
	/*else if (prev_item_on_board == GHOST_WALL)
	{
		gotoxy(prevCol, prevRow);
		cout << (char)GHOST_WALL;
	}*/
	else if (prev_item_on_board == EATEN || prev_item_on_board == EMPTY_CELL_BOARD) // todo- i changed here EMPTY_CELL. check it's ok
	{
		gotoxy(prevCol, prevRow);
		cout << (char)EATEN;
	}
}
