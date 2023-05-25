// This class controls the whole program's games.
// For each game, a new object of class Game created.

#ifndef GAME_MANAGER 
#define GAME_MANAGER
#include "Game.h"
#include "Operation.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class GameManager
{
	Game* pacman_game;
	int lives_manager;
	vector<string> screens;

public:

	GameManager();  // c'tor

	int getLivesManager() { return lives_manager; }
	void setLivesManager(int new_life) { lives_manager = new_life; }

	void printMenu();
	void printInstructions();
	void runGame(string& file_name, int level_choice);

};

#endif