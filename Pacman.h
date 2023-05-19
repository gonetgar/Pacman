#ifndef PACMAN
#define PACMAN

#include "Position.h"
#include "Operation.h"
#include "Board.h"

class Pacman
{
	static int lives_remaining;
	Position current_position;
	char direction;
	int score;
	int lives;
public:
	Pacman();
	int getScore() { return score; }
	void setScore(int new_score) { score = new_score; }
	int getALife() { return lives; }
	void setLife(int new_life) { lives = new_life; }
	void setRemainingLives(int new_life) { Pacman::lives_remaining = new_life; }

	Position& getCurrentPosition() { return current_position; }
	void placePacmanAtStartPosition();
	void pacmanMovement(Board& game_board, char pressed_key);
	void move(Board& game_board, int curr_row, int curr_col, int new_row, int new_col, int tunnel_row, int tunnel_col, bool side_tunnel);
	void crossATunnel(Board& game_board, int curr_row, int curr_col, int tunnel_row, int tunnel_col, bool side_tunnel);
	void crossRegularPath(Board& game_board, int curr_row, int curr_col, int new_row, int new_col, bool breadcrumb);
	void printPacman();
};
int Pacman::lives_remaining = 3;
#endif
