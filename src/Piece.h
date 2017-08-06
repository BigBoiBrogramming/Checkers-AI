#ifndef PIECE_H
#define PIECE_H

#include <set>
#include <deque>
#include "Team.h"
#include "Board.h"
#include "exceptions/AlreadyHasPieceException.h"

class Board;

using namespace std;

class Piece {
public:
	Piece(Board* board, Team team, tuple<int,int> coordinates);
	virtual ~Piece();
	void move(tuple<int,int> endTileCoord);
	set<deque<tuple<int,int> > > getAvailableMoves();
	friend ostream& operator<<(ostream& os, const Piece& p);
	Team getTeam();
	void setTeam(Team& t);
	tuple<int,int> getCoordinate();

protected:
	virtual set<deque<tuple<int,int> > > getAvailableSingleSquareMoves(tuple<int,int>& currentCoord);
	virtual set<deque<tuple<int,int> > > getAvailableAttacks(tuple<int,int>& currentCoord);
	Team team;
	Board* board;
	tuple<int,int> coordinate;
};

#endif
