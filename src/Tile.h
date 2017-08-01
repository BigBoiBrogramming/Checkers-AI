#ifndef TILE_H
#define TILE_H

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include "Piece.h"
#include "exceptions/PieceDoesNotExistException.h"

using namespace std;

class Piece;

class Tile {
public:
	Tile(tuple<int,int> coord);
	~Tile();
	bool hasPieceOnTile();
	void setPiece(Piece* p);
	Piece* removePieceFromTile();
	tuple<int,int> getCoordinates();
	Piece* getPiece();

private:
	bool pieceOnTile;
	Piece* piece;
	tuple<int,int> coordinate;
};

#endif
