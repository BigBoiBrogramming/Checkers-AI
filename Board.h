#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include "Team.h"
#include "Piece.h"

class Tile;

class Board {
public:
	Tile*** tiles;
	
	Board();
	~Board();
	void initializeTiles();
	void initializePieces();
	void print();
};

#endif
