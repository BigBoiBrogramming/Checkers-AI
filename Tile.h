#ifndef TILE_H
#define TILE_H

using namespace std;

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
	
	Tile();
	~Tile();
	bool hasPieceOnTile();
	Team getTeamOfPieceOnTile();
	void addPieceOnTile(Piece* newPiece);
	Piece* removePieceFromTile();

private:
	bool pieceOnTile_;
};

#endif
