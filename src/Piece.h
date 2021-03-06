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
	virtual set<deque<tuple<int,int> > > getAvailableMoves();
	friend ostream& operator<<(ostream& os, const Piece& p);
	Team getTeam();
	tuple<int,int> getCoordinates();
	virtual string getStringRepresentation();

protected:
	virtual set<deque<tuple<int,int> > > getAvailableSingleSquareMoves(tuple<int,int>& currentCoord);
	set<deque<tuple<int,int> > > getAvailableAttacks(tuple<int,int>& currentCoord);
	virtual void printMyself() const;
	// update a piece at the given coordinates to a king if needed
	void updateToKingIfNeeded();
	
	Team team;
	Board* board;
	tuple<int,int> coordinates;
};

#endif
