using namespace std;

#include <iostream>
#include "Piece.h"

class Tile {
public:
	Piece* piece_;
	
	Tile();
	~Tile();
	bool isPieceOnTile();
	void addPieceOnTile(Piece* newPiece);
	Piece* removePieceFromTile();

private:
	bool pieceOnTile_;
};
