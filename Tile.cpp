#include "Tile.h"

Tile::Tile(tuple<int,int> coord) : coordinates(coord)
{
	piece = NULL;
	pieceOnTile = false;
}

// check if piece is on tile
bool Tile::hasPieceOnTile()
{
	return pieceOnTile;
}

// removes and returns pointer to the piece on the tile
Piece* Tile::removePieceFromTile()
{
	pieceOnTile = false;
	Piece* tempPiece = piece;
	piece = NULL;
	return tempPiece;
}

void Tile::setPiece(Piece* p)
{	
	piece = p;
	
	if (this->piece == NULL) {
		pieceOnTile = false;
	} else {
		pieceOnTile = true;
	}
}

Tile::~Tile()
{
	if (piece != NULL) {
		delete piece;
	}
}

tuple<int,int> Tile::getCoordinates()
{
	return coordinates;
}

Piece* Tile::getPiece()
{
	return piece;
}
