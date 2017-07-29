#ifndef BOARD_H
#define BOARD_H

using namespace std;

#include "Tile.h"
#include "Team.h"
#include "Piece.h"

class Board {
public:
	Tile*** tiles;
	
	Board();
	~Board();
	void print();
};

#endif
