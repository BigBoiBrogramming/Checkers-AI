#include "King.h"

King::King(Board* board, Team team, tuple<int,int> coordinates) : Piece (board, team, coordinates)
{
}

// print the piece
ostream& operator<<(ostream& os, const King& k)
{
	string color;
	if (k.team == Team::red) {
		color = "R";
	} else {
		color = "B";
	}
	
	os << "k" << color;
	
	return os;
}
