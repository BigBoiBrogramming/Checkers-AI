#ifndef TILE_H
#define TILE_H

using namespace std;

#include <iostream>
#include "Piece.h"

class Tile {
public:
	Piece* piece_;
	
	Tile();
	~Tile();
	bool isPieceOnTile();
	Team getTeamOfPieceOnTile();
	void addPieceOnTile(Piece* newPiece);
	Piece* removePieceFromTile();

private:
	bool pieceOnTile_;
};

#endif
