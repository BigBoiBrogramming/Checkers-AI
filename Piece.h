
#include <iostream>

#include "Tile.h"
class Board;

class Piece {
public:
	Team team;
	Piece(Board*, Team);
	
	void move(Tile*);
	
	~Peace();
	
	set<tuple<int,int> > getAvailableMoves();
	
	set<vector<tuple<int,int> > > getAvailableAttacks();
	
	tuple<int,int> coordinates_;
	
	Team teamOfPiece_;

private:
	
	Board* boardPtr_;
	
	Tile* tileLocationOfPiece_;
	
	

};

#endif