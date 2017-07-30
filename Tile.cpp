#include "Tile.h"

Tile::Tile()
{
	// initialize here
	piece_ = NULL;
	pieceOnTile_ = false;
}

// check if piece is on tile
bool Tile::isPieceOnTile()
{
	return pieceOnTile_;
}

Team Tile::getTeamOfPieceOnTile() {
	
	if piece_ != NULL {
		return piece_->teamOfPiece_
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
	if (!pieceOnTile_) {
		pieceOnTile_ = true;
		piece_ = newPiece;
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
	if (pieceOnTile_) {
		pieceOnTile_ = false;
		Piece* pieceHolder = piece_;
		piece_ = NULL;
		return pieceHolder;
	}
	else {
		cerr << "There is no piece on this tile";
		return NULL;
	}
}

Tile::~Tile()
{
	if (piece_ != NULL) {
		delete piece_;
	}
}
