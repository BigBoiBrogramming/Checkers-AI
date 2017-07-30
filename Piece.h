#ifndef PIECE_H
#define PIECE_H

using namespace std;

#include "Team.h"
#include "Board.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <set>
#include <tuple>
#include <stack>

class Board;
class Tile;

class Piece {
public:
	Team team;
	tuple<int,int> coordinates;
	
	Piece(Board*, Team);
	~Piece();
	void move(Tile*);
	set<stack<tuple<int,int> > > getAvailableMoves();
	set<stack<tuple<int,int> > > getAvailableSingleSquareMoves(tuple<int,int> coord);
	set<stack<tuple<int,int> > > getAvailableAttacks(tuple<int,int> coord);
	friend ostream& operator<<(ostream&, const Piece&);

private:
	Board* board;
};

#endif
