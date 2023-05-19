#include "GameManager.h"

// c'tor
GameManager::GameManager()
{
	pacman_game = nullptr;
	lives_manager = 3;

	string file_name = "pacman_a.screen.txt";
	for (int i = 0; i < 3; i++)
	{
		screens.push_back(file_name);
		file_name[7]++;
	}
}

//void GameManager::initGame()
//{
//	lives_manager = 3;
//}

void GameManager::printMenu()
{
	int choice;
	char level_choice, screen_letter = FIRST_SCREEN;
	char screen_choice;
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
				//initGame();
				this->lives_manager = 3;
				cout << "Choose a file: \n a\n b\n c" << endl;
				cin >> screen_choice;
				screen_choice = screen_choice - 'a' + 1;
				runGame(screens[screen_choice - 1], level_choice);
				
			}
			else // STARTGAME - start at file 'a' and then proceed to the next games
			{
				//initGame();
				this->lives_manager = 3;
				vector<string>::iterator it = screens.begin();
				while ((it != screens.end()) && (lives_manager > 0))
				{
					runGame(*it, level_choice);
					++it;
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
void GameManager::runGame(string& file_name, int level_choice)
{
	ifstream board_game(file_name);

	if (!board_game)
		cout << "Error, file couldn't be opened." << endl << endl;
	else
	{
		pacman_game = new Game(board_game, level_choice, this->lives_manager);
		this->lives_manager = pacman_game->startGame(); // enjoy :)
		delete pacman_game;
	}

	board_game.close();
}
