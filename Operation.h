#ifndef OPERATION
#define OPERATION

#include <iostream>
using namespace std;
#include <windows.h>
#include <conio.h>
#include <process.h>

enum {
	BOARD_WIDTH = 20, // TODO -> CHANGE LATER TO 80
	BOARD_HEIGHT = 10, // TODO -> CHANGE LATER TO 24
	FIRST_SCREEN = 'a',
	SECOND_SCREEN = 'b',
	THIRD_SCREEN = 'c',
	EMPTY_CELL_BOARD = '%',
	PACMAN_BOARD = '@',
	GHOST_BOARD = '$',
	EATEN = ' ',
	WALLS_BOARD = '#',
	PACMAN_PRINT = (char)2, // ☻
	GHOST_PRINT = (char)5, // ♣
	EXIT_GAME = 9,
	INSTRUCTIONS = 8,
	STARTGAME = 1,
	STARTGAMEWITHBOARDS = 2,
	PAUSE = 1,
	BEST = 'a',
	GOOD = 'b',
	NOVICE = 'c',
	ESC = 27,
	DEFAULT = 1,
	GHOSTSNUM = 2,
	LEFT = 'a',
	RIGHT = 'd',
	UP = 'w',
	DOWN = 'x',
	STAY = 's',
	WALL = '#',
	GHOST_WALL = '-',
	SIDE_TUNNEL = '|',
	UP_DOWN_TUNNEL = '_',
	BREADCRUMB = '.',
	GHOST_UP = 1,
	GHOST_DOWN = 2,
	GHOST_RIGHT = 3,
	GHOST_LEFT = 4,
	FRUIT_UP = 1,
	FRUIT_DOWN = 2,
	FRUIT_RIGHT = 3,
	FRUIT_LEFT = 4,
};

void gotoxy(int x, int y);
void hideCursor();

#endif