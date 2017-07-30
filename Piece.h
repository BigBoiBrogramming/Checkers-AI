#ifndef PIECE_H
#define PIECE_H

using namespace std;
#include <iostream>
#include "Team.h"
#include <string>

class Board;

class Piece {
public:
	Team team;
	Board* board;
	Piece(Board*, Team);
	friend ostream& operator<<(ostream&, const Piece&);
};

#endif
