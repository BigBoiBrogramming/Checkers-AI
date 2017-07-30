#include "Piece.h"

Piece::Piece(Board* board, Team team)
{
	this->board = board;
	this->team = team;
}

ostream& operator<<(ostream& os, const Piece& p)
{
	string color;
	if (p.team == Team::red) {
		color = "R";
	} else {
		color = "B";
	}
	
	os << "n" << color;
	
	return os;
}