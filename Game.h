// This class controls the current game played at the time.
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

	int startGame(int* total_score);
	void gameCourse(int* total_score);
	void handleCollision(int total_score, char* pressed_key);
	bool checkCollisionPacmanAndGhost();
	void checkFruitCollision(int* total_score);
	void eatFruit(vector<Fruit>::iterator* it);
	void printScoreAndLife(int total_score);
	bool isValidKey(char key, char* last_movement);
	bool isGameEnded();
	void placeGhostsAtStartPosition();
	void createGhosts();
	void createFruits();
	void placePacmanAtStartPosition();
	
	~Game()
	{
		ghostArray.clear();
		fruitArray.clear();
	}

};

#endif