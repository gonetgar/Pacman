#include "Position.h"

bool Position::operator==(const Position& other) const
{
	if (this->row == other.row && this->col == other.col)
		return true;
	return false;
}

bool Position::operator!=(const Position& other) const
{
	if (this->row != other.row || this->col != other.col)
		return true;
	return false;
}