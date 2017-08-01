#include "Tile.h"

Tile::Tile(tuple<int,int> coord) : coordinate(coord)
{
	piece = NULL;
	pieceOnTile = false;
}

Tile::~Tile()
{
	// deallocate the piece on the tile if it exists
	if (piece != NULL) {
		delete piece;
	}
}

// return whether or not the tile has a piece on it
bool Tile::hasPieceOnTile()
{
	return pieceOnTile;
}

// sets the piece
void Tile::setPiece(Piece* p)
{	
	piece = p;
	
	if (this->piece == NULL) {
		pieceOnTile = false;
	} else {
		pieceOnTile = true;
	}
}

// removes and returns pointer to the piece on the tile
Piece* Tile::removePieceFromTile()
{
	if (!pieceOnTile) {
		PieceDoesNotExistException e = PieceDoesNotExistException(get<0>(coordinate), get<1>(coordinate));
		cerr << e.what();
		exit(1);
	}
	
	pieceOnTile = false;
	Piece* tempPiece = piece;
	piece = NULL;
	return tempPiece;
}

// returns the coordinate
tuple<int,int> Tile::getCoordinates()
{
	return coordinate;
}

// returns the piece
Piece* Tile::getPiece()
{
	if (!pieceOnTile) {
		PieceDoesNotExistException e = PieceDoesNotExistException(get<0>(coordinate), get<1>(coordinate));
		cerr << e.what();
		exit(1);
	}
	
	return piece;
}
