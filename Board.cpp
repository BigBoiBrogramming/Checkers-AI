#include "Board.h"

Board::Board()
{
	initializeTiles();
	initializePieces();
}

Board::~Board()
{
	// deallocate all tiles
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete tiles[i][j];
		}
		delete tiles[i];
	}
	delete[] tiles;
}

// create a 2D array of tiles
void Board::initializeTiles()
{
	tiles = new Tile**[8];
	
	for (int i = 0; i <  8; i++) {
		tiles[i] = new Tile*[8];
	}
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			tiles[i][j] = new Tile();
		}
	}
}

// place pieces on the board
void Board::initializePieces()
{
	// initialize black pieces
	for (int i = 0; i <  3; i++) {
		int spacer = (i+1) % 2;
		for (int j = 0; j < 7; j += 2) {
			tiles[i][j+spacer]->piece_ = new Piece(this, black);
		}
	}

	// initialize red pieces
	for (int i = 5; i <  8; i++) {
		int spacer = (i) % 2;
		for (int j = 0; j < 7; j += 2) {
			tiles[i][j+spacer]->piece_ = new Piece(this, red);
		}
	}
}

// print out the current state of the board
void Board::print()
{
	cout << "_________________________________________" << endl;
	
	for (int i = 0; i < 8; i++) {
		cout << "|";
		for (int j = 0; j < 8; j++) {
			if (tiles[i][j]->piece_ == NULL) {
				cout << " -- |";
			} else {
				cout << " " << *tiles[i][j]->piece_ << " |";
			}
			if (j == 7) {
				cout << endl;
			}
		}
		cout << "_________________________________________" << endl;
	}
}
