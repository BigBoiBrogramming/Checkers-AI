using namespace std;

#include <iostream>
#include "Piece.h"

class Tile {
public:
	Tile();

	bool isPieceOnTile();

	void addPieceOnTile(Piece* newPiece);

	Piece* removePieceFromTile();

	~Tile();


private:
	bool pieceOnTile_;

	Piece* piece_;

};
