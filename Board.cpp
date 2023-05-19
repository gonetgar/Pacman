#include "Board.h"

// c'tor // TODO - maybe delete?
//Board::Board(string& file_name)
//{
//	//ifstream board_game("board_pattern.txt");
//	file_name = file_name + ".txt";
//	ifstream board_game(file_name);
//
//	if (!board_game)
//	{
//		cout << "Error, file couldn't be opened." << endl;
//		exit(1);
//	}
//	else
//	{
//		// taking the board from file and insert its data to the board matrix
//		for (int row = 0; row < BOARD_HEIGHT; row++)
//		{
//			for (int column = 0; column < BOARD_WIDTH; column++)
//			{
//				board_game >> this->board[row][column];
//
//				if (!board_game)
//				{
//					cout << "Error reading file for element " << row << "," << column << endl;
//				}
//			}
//		}
//	}
//}

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

	//////////////////////////////////////////////////////////////////////////
	//ifstream board_game("board_pattern.txt");
	//file_name = file_name + ".txt";
	//ifstream board_game(file_name);
	//if (!board_game)
	//{
	//	cout << "Error, file couldn't be opened." << endl;
	//	exit(1);
	//}
	//else
	//{
	//	// taking the board from file and insert its data to the board matrix
	//	for (int row = 0; row < BOARD_HEIGHT; row++)
	//	{
	//		for (int column = 0; column < BOARD_WIDTH; column++)
	//		{
	//			board_game >> this->board[row][column];
	//
	//			if (!board_game)
	//			{
	//				cout << "Error reading file for element " << row << "," << column << endl;
	//			}
	//		}
	//	}
	//}
}

// prints the board to the screen, update number of breadcrumbs on board
void Board::printBoard(int* total_breadcrumbs)
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			switch (this->board[i][j])
			{
				case(EMPTY_CELL_BOARD): // '%'
				{
					cout << ' ';
					break;
				}
				case(BREADCRUMB): // '.'
				{
					(*total_breadcrumbs)++;
					cout << '.';
					break;
				}
				case(GHOST_BOARD): // '$' // if it's ghost, it counts as breadcrumb
				{
					(*total_breadcrumbs)++;
					cout << '.';
					break;
				}
				case(PACMAN_BOARD): // '@'		
				{
					cout << (char)PACMAN_PRINT;
					break;
				}
				//case(GHOST_BOARD): // '$'
				//{
				//	cout << GHOST_PRINT;
				//	break;
				//}
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