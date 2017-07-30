#include "Tile.h"

Tile::Tile(tuple<int,int> coord) : coordinates(coord)
{
	// initialize here
	piece = NULL;
	pieceOnTile = false;
}

// check if piece is on tile
bool Tile::hasPieceOnTile()
{
	return pieceOnTile;
}

Team Tile::getTeamOfPieceOnTile() {
	
	if (piece != NULL) {
		return piece->team;
	}
	else
	{
		cerr << "There is no piece on this tile";
	}
	
}

// add piece to tile via a new pointer
// throws error if there is already a piece on the tile
void Tile::addPieceOnTile(Piece* newPiece)
{
	if (!pieceOnTile) {
		pieceOnTile = true;
		piece = newPiece;
	}
	else
	{
		cerr << "There is a piece on this tile";
	}

}

// removes and returns pointer to the piece on the tile
// throws error if there is no piece on the tile
Piece* Tile::removePieceFromTile()
{
	if (pieceOnTile) {
		pieceOnTile = false;
		Piece* pieceHolder = piece;
		piece = NULL;
		return pieceHolder;
	}
	else {
		cerr << "There is no piece on this tile";
		return NULL;
	}
}

void Tile::setPiece(Piece* piece)
{
	this->piece = piece;
}

Tile::~Tile()
{
	if (piece != NULL) {
		delete piece;
	}
}
