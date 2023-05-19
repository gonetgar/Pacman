#include "Position.h"

bool Position::operator==(Position& other)
{
	if (this->row == other.row && this->col == other.col)
		return true;
	return false;
}

bool Position::operator!=(Position& other)
{
	if (this->row != other.row || this->col != other.col)
		return true;
	return false;
}