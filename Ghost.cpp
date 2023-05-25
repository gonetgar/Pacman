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

// ghosts trying to chase the pacman
void Ghost::moveBest(Board& game_board, vector<Ghost>& other_array, int num_ghosts, Position& pacPos)     /// for best - helper
{
	int curRow = this->current_position.getRow();
	int curCol = this->current_position.getCol();

	int pac_row = pacPos.getRow();
	int pac_col = pacPos.getCol();

	// Calculate distance between ghost and Pacman in each direction
	Distance distances[4];
	distances[0].val = abs(curRow - pac_row - 1) + abs(curCol - pac_col); // Up
	distances[0].direction = GHOST_UP;
	distances[1].val = abs(curRow - pac_row + 1) + abs(curCol - pac_col); // Down
	distances[1].direction = GHOST_DOWN;
	distances[2].val = abs(curRow - pac_row) + abs(curCol - pac_col + 1); // Right
	distances[2].direction = GHOST_RIGHT;
	distances[3].val = abs(curRow - pac_row) + abs(curCol - pac_col - 1); // Left
	distances[3].direction = GHOST_LEFT;

	// sort array // TODO
	for (int i = 0; i < 4 - 1; i++)
	{
		for (int j = 0; j < 4 - i - 1; j++)
		{
			if (distances[j].val > distances[j + 1].val)
			{
				Distance temp = distances[j];
				distances[j] = distances[j + 1];
				distances[j + 1] = temp;
			}
		}
	}

	int moved = 0;
	for (int i = 0; i < 4 && moved == 0; i++) // didn't move
	{
		Position next_ghost_position = this->getNextPosition(distances[i].direction);
		int new_row = next_ghost_position.getRow();
		int new_col = next_ghost_position.getCol();
		this->move(game_board, other_array, num_ghosts, new_row, new_col, &moved);
	}

	/*while (moved == 0)
	{
		Position next_ghost_position = this->getNextPosition(i + 1);
		int new_row = next_ghost_position.getRow();
		int new_col = next_ghost_position.getCol();
		this->move(game_board, other_array, num_ghosts, new_row, new_col, &moved);
		i++;
	}*/

	/*static int moved_matan = 0;
	int moved = 0;
	int curRow = this->current_position.getRow();
	int curCol = this->current_position.getCol();
	int pac_row = pacPos.getRow();
	int pac_col = pacPos.getCol();

	int best_direction = getBestDirection(game_board, other_array, num_ghosts, pacPos);

	switch (best_direction)
	{
	case GHOST_UP:
		this->move(game_board, other_array, num_ghosts, curRow - 1, curCol, &moved);
		cout << "moved: " << moved << " up";
		if (moved == 1)
			cout << "           ";
		break;
	case GHOST_DOWN:
		this->move(game_board, other_array, num_ghosts, curRow + 1, curCol, &moved);
		cout << "moved: " << moved << " down";
		if (moved == 1)
			cout << "           ";
		break;
	case GHOST_RIGHT:
		this->move(game_board, other_array, num_ghosts, curRow, curCol + 1, &moved);
		cout << "moved: " << moved << " right";
		if (moved == 1)
			cout << "           ";
		break;
	case GHOST_LEFT:
		this->move(game_board, other_array, num_ghosts, curRow, curCol - 1, &moved);
		cout << "moved: " << moved << " left";
		if (moved == 1)
			cout << "           ";
		break;
	}*/
}

int Ghost::getBestDirection(Board& game_board, vector<Ghost>& other_array, int num_ghosts, Position& pacPos)
{
	int curRow = this->current_position.getRow();
	int curCol = this->current_position.getCol();

	int pac_row = pacPos.getRow();
	int pac_col = pacPos.getCol();

	// Calculate distance between ghost and Pacman in each direction
	int distances[4];
	distances[GHOST_UP - 1] = abs(curRow - pac_row - 1) + abs(curCol - pac_col); // Up
	distances[GHOST_DOWN - 1] = abs(curRow - pac_row + 1) + abs(curCol - pac_col); // Down
	distances[GHOST_RIGHT - 1] = abs(curRow - pac_row) + abs(curCol - pac_col + 1); // Right
	distances[GHOST_LEFT-1] = abs(curRow - pac_row) + abs(curCol - pac_col - 1); // Left


	// sort array // TODO
	//for (int i = 0; i < 4 - 1; i++)
	//	for (int j = 0; j < 4 - i - 1; j++)
	//		if (distances[j] > distances[j + 1])
	//			swap(&distances[j], &distances[j + 1]);

	//int moved = 0, i=0;

	//while(moved != 0) // didn't move
	//{
	//	Position next_ghost_position = this->getNextPosition(i + 1);
	//	int new_row = next_ghost_position.getRow();
	//	int new_col = next_ghost_position.getCol();
	//	this->move(game_board, other_array, num_ghosts, new_row, new_col, &moved);
	//	i++;
	//}







	//
	
	
	// Find the minimum distance and return the corresponding direction
	int minDistance = distances[GHOST_UP-1];
	int bestDirection = -1; // GHOST_UP;
	bool collision = false;

	for (int i = 0; i < 4; i++)
	{
		Position next_ghost_position = this->getNextPosition(i+1);
		if (distances[i] <= minDistance && 
			game_board.getCellItem(next_ghost_position.getRow(), next_ghost_position.getCol()) != WALL && 
			game_board.getCellItem(next_ghost_position.getRow(), next_ghost_position.getCol()) != SIDE_TUNNEL &&
			game_board.getCellItem(next_ghost_position.getRow(), next_ghost_position.getCol()) != UP_DOWN_TUNNEL)
			// todo add check if there is a ghost
		{
			// check if it's not ghost
			for (int i = 0; i < num_ghosts; i++)
			{
				if (next_ghost_position == other_array[i].current_position)
					collision = true;
			}


			if (!collision)
			{
				minDistance = distances[i];
				bestDirection = i + 1;
			}
		}
	}

	return bestDirection;
}

// receives direction (right, left, etc) and returns the next position
Position& Ghost::getNextPosition(int direction)
{
	Position next_pos;

	switch (direction)
	{
	case GHOST_UP:
		next_pos.setRow(this->current_position.getRow() - 1);
		next_pos.setCol(this->current_position.getCol());
		break;
	case GHOST_DOWN:
		next_pos.setRow(this->current_position.getRow() + 1);
		next_pos.setCol(this->current_position.getCol());
		break;
	case GHOST_RIGHT:
		next_pos.setRow(this->current_position.getRow());
		next_pos.setCol(this->current_position.getCol()+1);
		break;
	case GHOST_LEFT:
		next_pos.setRow(this->current_position.getRow());
		next_pos.setCol(this->current_position.getCol()-1);
		break;
	default:
		break;
	}

	return next_pos;
}


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
