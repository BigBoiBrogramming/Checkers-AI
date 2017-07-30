#include "King.h"

King::King(Board* board, Team team) : Piece (board, team)
{
	// initialize here
}

ostream& operator<<(ostream& os, const King& p)
{
	string color;
	if (p.team == Team::red) {
		color = "R";
	} else {
		color = "B";
	}
	
	os << "k" << color;
	
	return os;
}
