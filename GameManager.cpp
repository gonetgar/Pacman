#include "GameManager.h"

void GameManager::printMenu()
{
	int choice;
	char level_choice, screen_letter = 'a';
	string file_name = "pacman_a.screen.txt";

	do {
		cout << "(1) Start a new game" << endl;
		cout << "(2) Start a new game with specific screen" << endl;
		cout << "(8) Present instructions and keys" << endl;
		cout << "(9) EXIT" << endl;
		cin >> choice;
		
		if (choice == STARTGAME || choice == STARTGAMEWITHBOARDS)
		{
			cout << "Choose game level:" << endl;
			cout << "(a) BEST" << endl << "(b) GOOD" << endl << "(c) NOVICE" << endl;
			cin >> level_choice;
			
			if(choice == STARTGAMEWITHBOARDS) // choose screen and play one game
			{
				cout << "Choose a file: (a, b, or c)" << endl;
				cin >> screen_letter;
				file_name[7] = screen_letter;
				runGame(file_name, level_choice, 3);
			}
			else // STARTGAME - start at file 'a' and then proceed to the next games
			{
				while (screen_letter >= 'a' && screen_letter <= 'c')
				{
					int previous_lives;
					// TODO think about the lives. maybe static?
					if (screen_letter == 'a') // the first game
						previous_lives = 3;
					else


					runGame(file_name, level_choice);

					// move to the next screen
					screen_letter++;
					file_name[7] = screen_letter;
				}
			}
		}
		else
		{
			switch (choice)
			{
			case INSTRUCTIONS:
				printInstructions();
				break;
			case EXIT_GAME:
				cout << "Bye bye :-)" << endl;
				break;
			default:
				cout << "Error! please press 1, 2, 8 or 9." << endl;
				break;
			}
		}

	} while (choice != EXIT_GAME);
}

void GameManager::printInstructions()
{
	cout << endl << "Game instructions:" << endl;
	cout << "Start the game by pressing one of the keys to move:" << endl;
	cout << "A - left" << endl;
	cout << "D - right" << endl;
	cout << "W - up" << endl;
	cout << "X - down" << endl;
	cout << "S - stay" << endl;
	cout << "Your goal is to eat all of the breadcrumbs on the screen" << endl;
	cout << "You start the game with 3 lives and score 0." << endl;
	cout << "You get a point for each breadcrumbs you eat. You lose a life for each time a ghost meets you." << endl;
	cout << "You win when you finish eating all of the breadcrumbs" << endl;
	cout << "The game ends when you lose all your lives by being caught by the ghosts." << endl;
	cout << "And most importanatly: HAVE FUN :)" << endl << endl;
}

// opens the board file and initiate the game
void GameManager::runGame(string& file_name, int level_choice, int current_lives)
{
	ifstream board_game(file_name);

	if (!board_game)
		cout << "Error, file couldn't be opened." << endl << endl;
	else
	{
		pacman_game = new Game(board_game, level_choice, current_lives);
		pacman_game->startGame(); // enjoy :)
		delete pacman_game;
	}

	board_game.close();
}
