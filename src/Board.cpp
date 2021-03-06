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

// initialize a 2D array of tiles
void Board::initializeTiles()
{
	tiles = new Tile**[8];
	
	for (int i = 0; i <  8; i++) {
		tiles[i] = new Tile*[8];
	}
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			tiles[i][j] = new Tile(make_tuple(i, j));
		}
	}
}

// place pieces on the board in their starting state
void Board::initializePieces()
{
	// initialize red pieces
	for (int i = 0; i <  8; i++) {
		int startIndex = i % 2;
		for (int j = startIndex; j < 3; j+=2) {
			tiles[j][i]->setPiece(new Piece(this, red, make_tuple(i, j)));
		}
	}
	
	// initialize black pieces
	for (int i = 0; i <  8; i++) {
		int startIndex = 6 - (i % 2);
		for (int j = startIndex; j < 8; j+=2) {
			tiles[j][i]->setPiece(new Piece(this, black, make_tuple(i, j)));
		}
	}
}

// print out the current state of the board
void Board::print()
{
	cout << "    0    1    2    3    4    5    6    7" << endl;
	cout << "  _________________________________________" << endl;
	
	for (int i = 7; i >= 0; i--) {
		cout << i << " |";
		for (int j = 0; j < 8; j++) {
			if (!tiles[i][j]->hasPieceOnTile()) {
				cout << " -- |";
			} else {
				cout << " " << *tiles[i][j]->getPiece() << " |";
			}
			if (j == 7) {
				cout << endl;
			}
		}
		cout << "  _________________________________________" << endl;
	}
}

// return the tiles
Tile*** Board::getTiles()
{
	return tiles;
}

// return a string representation of the board
string Board::getBoardString()
{
	string boardString = "";
	
	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			// if there is no piece
			if (!tiles[i][j]->hasPieceOnTile()) {
				boardString += "--";
			} else {
				boardString += tiles[i][j]->getPiece()->getStringRepresentation();
			}
			// if the end of the row is reached
			if (j == 7) {
				boardString += "||";
			}
		}
	}
	
	return boardString;
}

Board Board::getDeepCopy()
{
	Board bCopy = Board();
	
	// delete all the default pieces
	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			if (bCopy.tiles[i][j]->hasPieceOnTile()) {
				bCopy.tiles[i][j]->removePieceFromTile();
			}
		}
	}
	
	// add in all the new pieces
	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			if (tiles[i][j]->hasPieceOnTile()) {
				Piece* realPiece = tiles[i][j]->getPiece();
				Piece* pCopy = new Piece(&bCopy, realPiece->getTeam(), realPiece->getCoordinates());
				bCopy.tiles[i][j]->setPiece(pCopy);
			}
		}
	}
	
	return bCopy;
}
