#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
	King(Board* board, Team team, tuple<int,int> coordinates);
	set<deque<tuple<int,int> > > getAvailableMoves();

private:
	set<deque<tuple<int,int> > > getAvailableSingleSquareMoves(tuple<int,int>& currentCoord);
	set<deque<tuple<int,int> > > getAvailableAttacks(tuple<int,int>& currentCoord, set<tuple<int,int> >& jumpedCoordinates);
	bool pieceAlreadyJumped(set<tuple<int,int> >& jumpedCoordinates, pair<int,int> checkCoordinate) const;
	void printMyself() const;
	string getStringRepresentation();
};

#endif
