#ifndef TILE_H
#define TILE_H

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include "Piece.h"

using namespace std;

class Piece;

class Tile {
public:
	Tile(tuple<int,int> coord);
	~Tile();
	bool hasPieceOnTile();
	void addPieceOnTile(Piece* newPiece);
	void setPiece(Piece* piece);
	Piece* removePieceFromTile();
	tuple<int,int> getCoordinates();
	Piece* getPiece();

private:
	bool pieceOnTile;
	Piece* piece;
	tuple<int,int> coordinates;
};

#endif
