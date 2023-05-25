#include "Game.h"

// c'tor
Game::Game(ifstream& board_file, int chosen_level, int current_lives)
{
	this->total_breadcrumbs = 0;
	this->num_of_fruits = 1; // TODO -> CHANGE LATER TO whatever
	this->num_of_ghosts = 1; // TODO -> CHANGE LATER TO whatever
	this->level = chosen_level;
	this->game_pause = true;
	this->player.setLife(current_lives);
	this->board.createBoard(board_file); // saves pacman position
	
	system("cls");	// clear screen
}

// returns the lives of the player in the end of the specific game
int Game::startGame()
{
	// print board and all entities in their starting locations (get from file)
	board.printBoardAndSaveCreaturesPositions(&total_breadcrumbs);
	this->placePacmanAtStartPosition();
	createGhosts();
	
	for (int i = 0; i < ghostArray.size(); i++)
		ghostArray[i].printGhost();

	printScoreAndLife();


	// start the game :-)
	this->gameCourse();

	return player.getALife();
}

// main game function that handles the entire game
void Game::gameCourse()
{
	// TODO later: delete this before uploading to mama (for convenience only)
	char RETURN_TO_MENU = '0';
	////////////////////////////////////////////////////////////

	char pressed_key = PAUSE; // start of the game
	bool collision = false;
	int turn = 1;

	do
	{
		hideCursor();
		if (_kbhit())
		{
			char curr_key = _getch();
			curr_key = (char)tolower(curr_key);

			char last_movement;
			if (this->isValidKey(curr_key, &last_movement));
			pressed_key = curr_key;

			if (pressed_key == PAUSE)
				this->game_pause = true;
			else if (pressed_key == RETURN_TO_MENU) // TODO -> DELETE LATER
			{////
				player.setLife(0);////
			}//////
			else if (pressed_key == ESC)
			{
				gotoxy(0, 25);
				cout << "\nGame paused, press ESC again to continue.\n";
				this->game_pause = true;
				curr_key = _getch();

				while (curr_key != ESC)
				{
					this->game_pause = true;
					curr_key = _getch();
				}
				gotoxy(0, 25);
				cout << "                                          ";
				this->game_pause = false;
				pressed_key = last_movement;
			}
			else
				this->game_pause = false;
		}

		if (!this->game_pause)
		{
			switch (this->level) /// Todo level int in game
			{
			case NOVICE: // Novice
			{
				if (turn % 20 == 0) // the game level. every 20 turns do random
				{
					for (int i = 0; i < num_of_ghosts; i++)
					{
						ghostArray[i].setLastDir(ghostArray[i].ghostMovement(this->board, ghostArray, num_of_ghosts));
						//ghostArray[i].last_dir = ghostArray[i].ghostMovement(this->board, ghostArray, num_of_ghosts);
					}
				}
				else  // take the previous movement
				{
					for (int i = 0; i < num_of_ghosts; i++)
					{
						ghostArray[i].moveNR(this->board, ghostArray, num_of_ghosts, ghostArray[i].getLastDir());   /// need also to add to ghosts int of last move, and check for colission if stays.
					}
				}
				break;
			}
			case GOOD:  // Good
			{
				if (turn % 20 == 0) // every 20 turns do random
				{
					for (int i = 0; i < num_of_ghosts; i++)
					{
						ghostArray[i].setLastDir(ghostArray[i].ghostMovement(this->board, ghostArray, num_of_ghosts));
						//ghostArray[i].last_dir = ghostArray[i].ghostMovement(this->board, ghostArray, num_of_ghosts);
						if (checkCollision() == true)
							handleCollision(&pressed_key);
					}
				}
				else if ((turn % 20) >= 1 || (turn % 20) <= 5) // take the previous movement
				{
					for (int i = 0; i < num_of_ghosts; i++)
					{
						ghostArray[i].moveNR(this->board, ghostArray, num_of_ghosts, ghostArray[i].getLastDir());
						if (checkCollision() == true)
							handleCollision(&pressed_key);
					}
				}
				else
				{
					for (int i = 0; i < num_of_ghosts; i++) {
						ghostArray[i].moveBest(this->board, ghostArray, num_of_ghosts, player.getCurrentPosition());
						if (checkCollision() == true)
							handleCollision(&pressed_key);
					}
				}
				break;
			}
			case BEST: // best
			{
				for (int i = 0; i < num_of_ghosts; i++)
				{
					ghostArray[i].moveBest(this->board, ghostArray, num_of_ghosts, player.getCurrentPosition());
					if (checkCollision() == true)
						handleCollision(&pressed_key);
				}
				break;
			}
			}

			//Sleep(100);

			//if (turn == 1)
			//{
			//	this->board.setCellItem(1, 2, '.');
			//	
			//	// TODO -> CHANGE LATER TO THIS:
			//	/*this->board.setCellItem(3, 3, '.');
			//	this->board.setCellItem(3, 76, '.');
			//	this->board.setCellItem(18, 3, '.');
			//	this->board.setCellItem(18, 76, '.');*/
			//}

			if (turn % 5 == 0)  // fruits move every 5 turns
			{
				// todo - > bring back later
				/*for (int i = 0; i < this->num_of_fruits; i++)
				{
					fruitArray[i].fruitMovement(this->board, fruitArray, this->num_of_fruits);
					if (checkCollision() == true)
						handleCollision(&pressed_key);
				}*/
			}

			if (pressed_key != 's')
			{
				player.pacmanMovement(this->board, pressed_key);
				printScoreAndLife();
			}

			if (checkCollision() == true)
			{
				handleCollision(&pressed_key);
			}

			Sleep(100);
			turn++;
		}
		//

		/*if (!this->game_pause)
		{
			if (turn % 2 == 0)
			{
				for (int i = 0; i < num_of_ghosts; i++)
				{
					ghostArray[i].ghostMovement(this->board, ghostArray, num_of_ghosts);
					if (checkCollision() == true)
					{
						handleCollision(&pressed_key);
					}
				}

				Sleep(100);
			}



			if (turn == 1)
			{
				this->board.setCellItem(3, 3, '.');
				this->board.setCellItem(3, 76, '.');
				this->board.setCellItem(18, 3, '.');
				this->board.setCellItem(18, 76, '.');
			}

			if (pressed_key != 's')
			{
				player.pacmanMovement(this->board, pressed_key);
				printScoreAndLife();
			}

			if (checkCollision() == true)
			{
				handleCollision(&pressed_key);
			}

			Sleep(100);
			turn++;
		}*/

	} while (!isGameEnded());


	if (player.getALife() == 0)  // lost the game
		cout << endl << endl << "Game Over :(" << endl;
	else						// won the game
		cout << endl << "WINNER !!!" << endl;

	cout << "Total score: " << player.getScore() << " out of " << total_breadcrumbs << "." << endl;
	cout << "Press any key to continue";
	_getch();
	system("cls"); // clear screen
}

void Game::handleCollision(char* pressed_key) // between pacman and ghost
{
	for (int i = 0; i < num_of_ghosts;  i++)
		ghostArray[i].reservePreviousItem(board); // print previous item on the board

	placeGhostsAtStartPosition();

	for (int i = 0; i < num_of_ghosts; i++)
		ghostArray[i].printGhost();

	//player.placePacmanAtStartPosition();
	this->placePacmanAtStartPosition();
	//player.printPacman();
	player.setLife(player.getALife() - 1);
	printScoreAndLife();
	*pressed_key = PAUSE; // pause the game until player press another key
	game_pause = true;
}

bool Game::checkCollision() // between pacman and ghost
{
	for (int i = 0; i < num_of_ghosts; i++)
	{
		if (ghostArray[i].getCurrentPosition() == player.getCurrentPosition())
			return true;
	}

	return false;
}

void Game::printScoreAndLife()
{
	gotoxy(15, 24);
	cout << "Remaining Lives: " << player.getALife();
	gotoxy(45, 24);
	cout << "Score: " << player.getScore();
}

bool Game::isValidKey(char key, char* last_movement)
{
	if (key == LEFT || key == RIGHT || key == UP || key == DOWN || key == STAY)
	{
		*last_movement = key;
		return true;
	}
	else if (key == ESC)
		return true;

	return false;
}

bool Game::isGameEnded()
{
	if (player.getALife() == 0 || player.getScore() == this->total_breadcrumbs)
		return true;
	return false;
}

// place ghosts at the start of each game
void Game::placeGhostsAtStartPosition()
{
	vector<Position> ghosts_pos = this->board.getghostsPositions();

	for (int i = 0; i < this->num_of_ghosts; i++)
	{
		ghostArray[i].setCurrentPosition(ghosts_pos[i]);
	}
}

// create the ghosts objects and place them at the initial place on board
void Game::createGhosts()
{
	this->num_of_ghosts = board.getghostsPositions().size();

	for (int i = 0; i < this->num_of_ghosts; i++)
	{
		int row = board.getghostsPositions()[i].getRow();
		int col = board.getghostsPositions()[i].getCol();
		ghostArray.push_back(Ghost(row, col));
	}
}

void Game::placePacmanAtStartPosition()
{
	player.setCurrentPosition(board.getPacmanPosition());

	// todo -> check if necessary
	gotoxy(player.getCurrentPosition().getCol(), player.getCurrentPosition().getRow());
	cout << (char)PACMAN_PRINT;
}
