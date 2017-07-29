#ifndef PIECE_H
#define PIECE_H

using namespace std;

#include "Team.h"
#include "Board.h"

class Piece {
public:
	Team team;
	Piece(Board*, Team);
};

#endif
