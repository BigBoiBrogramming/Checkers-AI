#ifndef PIECE_H
#define PIECE_H


using namespace std;

#include <cstdlib>
#include <iostream>
#include <set>
#include <tuple>
#include <stack>

#include "Team.h"
#include "Board.h"

class Board;
class Tile;

class Piece {
public:
	Team team;
	Piece(Board*, Team);
	~Piece();
	
	void move(Tile*);
	
	
	
	set<stack<tuple<int,int> > > getAvailableMoves();
	
	set<stack<tuple<int,int> > > getAvailableAttacks(tuple<int,int> coord);
	
	friend ostream& operator<<(ostream&, const Piece&);
	
	tuple<int,int> coordinates_;
	
	Team teamOfPiece_;

private:
	
	Board* boardPtr_;
	
	Tile* tileLocationOfPiece_;
	
	

};

#endif