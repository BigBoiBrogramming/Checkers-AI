#ifndef PIECE_H
#define PIECE_H

#include <deque>
#include <set>
#include "Board.h"
#include "exceptions/AlreadyHasPieceException.h"
#include "Team.h"

class Board;

using namespace std;

class Piece {
public:
	Piece(Board* board, Team team, tuple<int,int> coordinates);
	virtual ~Piece();
	int move(deque<tuple<int,int> >& move);
	set<deque<tuple<int,int> > > getAvailableMoves();
	friend ostream& operator<<(ostream& os, const Piece& p);
	Team getTeam();
	tuple<int,int> getCoordinates();

protected:
	virtual set<deque<tuple<int,int> > > getAvailableSingleSquareMoves(tuple<int,int>& currentCoord);
	virtual set<deque<tuple<int,int> > > getAvailableAttacks(tuple<int,int>& currentCoord);
	
	Team team;
	Board* board;
	tuple<int,int> coordinates;
};

#endif
