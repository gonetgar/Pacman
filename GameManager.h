#ifndef GAME_MANAGER 
#define GAME_MANAGER
#include "Game.h"
#include "Operation.h"
#include <iostream>
#include <string>
using namespace std;

class GameManager
{
	Game* pacman_game;
	// add: Pacman* player;
public:
	GameManager() { pacman_game = nullptr; } // c'tor
	void printMenu();
	void printInstructions();
	void runGame(string& file_name, int level_choice, int current_lives);

};

#endif