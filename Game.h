#ifndef GAME 
#define GAME

#include "Pacman.h"
#include "Ghost.h"
#include "Board.h"
#include "Operation.h"
#include "Fruit.h"
#include <vector>
#include <string>

class Game
{
	int total_breadcrumbs;
	int num_of_ghosts;
	int num_of_fruits;
	int level;
	bool game_pause;
	Board board;
	Pacman player;
	vector<Ghost> ghostArray;
	vector<Fruit> fruitArray;
public:
	Game(ifstream& board_file, int chosen_level, int current_lives);
	int getNumOfBreadcrumbs() { return total_breadcrumbs; }
	int getNumOfGhosts() { return num_of_ghosts; }
	int getNumOfFruits() { return num_of_fruits; }
	int getLevel() { return level; }
	vector<Ghost>& getGhostsArray() { return ghostArray; }
	vector<Fruit>& getFruitsArray() { return fruitArray; }

	void startGame();
	void gameCourse();
	void handleCollision(char* pressed_key);
	bool checkCollision();
	void printScoreAndLife();
	bool isValidKey(char key, char* last_movement);
	bool isGameEnded();
	void placeGhostsAtStartPosition();
	void createGhosts();

	

	~Game()
	{
		ghostArray.clear();
		fruitArray.clear();
	}

};

#endif