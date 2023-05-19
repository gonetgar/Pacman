#ifndef POSITION
#define POSITION

#include <iostream>
using namespace std;

class Position
{
	int row;
	int col;
public:
	Position(int x = 0, int y = 0) : row(x), col(y) {} // default c'tor
	int getRow() { return row; }
	int getCol() { return col; }
	void setRow(int x) { row = x; }
	void setCol(int y) { col = y; }
	bool operator==(Position& other);
	bool operator!=(Position& other);
};

#endif
