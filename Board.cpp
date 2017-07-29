#include "Board.h"
#include "Piece.h"

Board::Board()
{
	// initialize tiles
	tiles = new Tile**[8];
	
	for (int i = 0; i <  8; i++) {
		tiles[i] = new Tile*[8];
	}
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			tiles[i][j] = new Tile();
		}
	}

	// initialize black pieces
	for (int i = 0; i <  2; i++) {
		int spacer = (i+1) % 2;
		for (int j = 0; j < 7; j += 2) {
			tiles[i][j+spacer]->piece_ = new Piece(this, black);
		}
	}

	// initialize red pieces
	for (int i = 5; i <  7; i++) {
		int spacer = (i) % 2;
		for (int j = 0; j < 7; j += 2) {
			tiles[i][j+spacer]->piece_ = new Piece(this, red);
		}
	}
}
