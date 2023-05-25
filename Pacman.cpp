#include "Pacman.h"

Pacman::Pacman()
{
	// set starting position:
	//placePacmanAtStartPosition(); // TODO - check if still necessary
	direction = 's'; // set default direction to "stay"
	score = 0;
	lives = 3;
}

//void Pacman::placePacmanAtStartPosition()
//{
//	current_position.setRow(6);
//	current_position.setCol(9);
//
//	// TODO -> LATER CHANGE TO THIS:
//	//current_position.setRow(9);
//	//current_position.setCol(39);
//}

// controlls the movement of pacman
void Pacman::pacmanMovement(Board& game_board, char pressed_key)
{
	int currRow = this->current_position.getRow();
	int currCol = this->current_position.getCol();

	switch (pressed_key)
	{
	case UP:
		move(game_board, currRow, currCol, currRow - 1, currCol, 22, 38, false);
		break;
	case DOWN:
		move(game_board, currRow, currCol, currRow + 1, currCol, 1, 38, false);
		break;
	case RIGHT:
		move(game_board, currRow, currCol, currRow, currCol + 1, 12, 1, true);
		break;
	case LEFT:
		move(game_board, currRow, currCol, currRow, currCol - 1, 12, 78, true);
		break;
	}
}

void Pacman::move(Board& game_board, int curr_row, int curr_col, int new_row, int new_col, int tunnel_row, int tunnel_col, bool side_tunnel)
{
	char tunnel;
	side_tunnel ? (tunnel = SIDE_TUNNEL) : (tunnel = UP_DOWN_TUNNEL);

	char new_position_on_board = game_board.getCellItem(new_row, new_col);

	if (new_position_on_board != WALL) // && new_position_on_board != GHOST_WALL) // not a wall
	{
		if (new_position_on_board == tunnel)
		{
			this->crossATunnel(game_board, curr_row, curr_col, tunnel_row, tunnel_col, side_tunnel);
		}
		else if (new_position_on_board == BREADCRUMB)
		{
			crossRegularPath(game_board, curr_row, curr_col, new_row, new_col, true);
		}
		else if (new_position_on_board == ' ')
		{
			crossRegularPath(game_board, curr_row, curr_col, new_row, new_col, false);
		}
	}
	else // a wall
	{
		gotoxy(curr_col, curr_row); // stay in the same place
		cout << (char)PACMAN_PRINT;
	}
}

// sends pacman through the tunnel
void Pacman::crossATunnel(Board& game_board, int curr_row, int curr_col, int tunnel_row, int tunnel_col, bool side_tunnel)
{
	gotoxy(tunnel_col, tunnel_row); // place pacman at new position-> out of the new tunnel
	cout << (char)PACMAN_PRINT;

	// set pacman's new position
	if (side_tunnel)
		this->current_position.setCol(tunnel_col);
	else
		this->current_position.setRow(tunnel_row);
	gotoxy(curr_col, curr_row); // place ' ' at his old location
	cout << ' ';

	curr_row = this->current_position.getRow();
	curr_col = this->current_position.getCol();
	if (game_board.getCellItem(curr_row, curr_col) == BREADCRUMB)
		this->score++;
}

void Pacman::crossRegularPath(Board& game_board, int curr_row, int curr_col, int new_row, int new_col, bool breadcrumb)
{
	// place pacman at new position
	gotoxy(new_col, new_row);
	cout << (char)PACMAN_PRINT;

	// place ' ' at previous position
	gotoxy(curr_col, curr_row);
	cout << ' ';

	// change pacman's position, update board
	this->current_position.setRow(new_row);
	this->current_position.setCol(new_col);

	// update score if he ate a breadcrumb
	if (breadcrumb)
	{
		game_board.setCellItem(new_row, new_col, ' ');
		this->score++;
	}
}

//void Pacman::printPacman()
//{
//	gotoxy(this->current_position.getCol(), this->current_position.getRow());
//	cout << (char)PACMAN_PRINT;
//}
