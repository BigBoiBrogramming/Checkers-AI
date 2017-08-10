#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "exceptions/PieceDoesNotExistException.h"
#include "Piece.h"

using namespace std;

class Piece;

class Tile {
public:
	Tile(tuple<int,int> coord);
	~Tile();
	bool hasPieceOnTile();
	void setPiece(Piece* p);
	void removePieceFromTile();
	Piece* getPiece();

private:
	bool pieceOnTile;
	Piece* piece;
	tuple<int,int> coordinates;
};

#endif
