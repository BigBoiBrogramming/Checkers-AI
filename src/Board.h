#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"

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
	string getBoardString();
	Board getDeepCopy();
	
private:
	Tile*** tiles;
};

#endif
