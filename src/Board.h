#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include "Team.h"
#include "Piece.h"

using namespace std;

class Tile;

class Board {
public:
	Board();
	~Board();
	void initializeTiles();
	void initializePieces();
	void print();
	Tile*** getTiles();
	
private:
	Tile*** tiles;
};

#endif
