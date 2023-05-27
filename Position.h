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
	const int getRow() const { return row; }
	const int getCol() const { return col; }
	void setRow(int x) { row = x; }
	void setCol(int y) { col = y; }
	bool operator==(const Position& other) const;
	bool operator!=(const Position& other) const;
};

#endif
