#include "Board.h"

// gets a reference to a file, reads from the file and places it in the board matrix
void Board::createBoard(ifstream& board_file)
{
	// taking the board from file and insert its data to the board matrix
	for (int row = 0; row < BOARD_HEIGHT; row++)
	{
		for (int column = 0; column < BOARD_WIDTH; column++)
		{
			board_file >> this->board[row][column];

			if (!board_file)
			{
				cout << "!!!!!!!!!Error reading file for element " << row << "," << column << endl;
			}
		}
	}
}

// prints the board to the screen, update number of breadcrumbs on board
void Board::printBoardAndSaveCreaturesPositions(int* total_breadcrumbs)
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			switch (this->board[i][j])
			{
				case(EMPTY_CELL_BOARD): // '%'
				{
					this->board[i][j] = EATEN;
					cout << this->board[i][j];
					break;
				}
				case(GHOST_BOARD): // '$' if it's ghost, it counts as breadcrumb (the ghosts are just hovering over the board without changing the array)
				{
					// add this location to the ghosts initial position
					ghostsPositions.push_back(Position(i, j));
					this->board[i][j] = (char)BREADCRUMB;
					cout << (char)BREADCRUMB;
					(*total_breadcrumbs)++;
					break;
				}
				case(BREADCRUMB): // '.'
				{
					(*total_breadcrumbs)++;
					cout << (char)BREADCRUMB;
					break;
				}
				case(PACMAN_BOARD): // '@'		
				{
					pacmanPosition.setRow(i); // save pacman's position on the board
					pacmanPosition.setCol(j);
					this->board[i][j] = (char)EATEN;
					cout << (char)PACMAN_PRINT;
					break;
				}
				default: // default is to print what's on the board
				{
					cout << this->board[i][j];
					break;
				}
			}
		}
		cout << endl;
	}
}