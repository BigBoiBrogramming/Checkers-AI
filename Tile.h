#ifndef TILE_H
#define TILE_H

#include "Piece.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>

class Piece;

class Tile {
public:
	Piece* piece;
	tuple<int,int> coordinates;
	
	Tile(tuple<int,int> coord);
	~Tile();
	bool hasPieceOnTile();
	Team getTeamOfPieceOnTile();
	void addPieceOnTile(Piece* newPiece);
	void setPiece(Piece* piece);
	Piece* removePieceFromTile();

private:
	bool pieceOnTile;
};

#endif
