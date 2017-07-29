#ifndef PIECE_H
#define PIECE_H

using namespace std;

#include "Team.h"

class Board;

class Piece {
public:
	Team team;
	Piece(Board*, Team);
};

#endif
