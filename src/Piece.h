#ifndef PIECE_H
#define PIECE_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <set>
#include <tuple>
#include <stack>
#include "Team.h"
#include "Board.h"
#include "exceptions/AlreadyHasPieceException.h"

class Board;
class Tile;

using namespace std;

class Piece {
public:
	Piece(Board* board, Team team, tuple<int,int> coordinates);
	virtual ~Piece();
	void move(tuple<int,int>& endTileCoord);
	set<stack<tuple<int,int> > > getAvailableMoves();
	virtual set<stack<tuple<int,int> > > getAvailableSingleSquareMoves(tuple<int,int>& currentCoord);
	virtual set<stack<tuple<int,int> > > getAvailableAttacks(tuple<int,int>& currentCoord);
	friend ostream& operator<<(ostream& os, const Piece& p);
	Team getTeam();
	void setTeam(Team& t);
	tuple<int,int> getCoordinate();

protected:
	Team team;
	Board* board;
	tuple<int,int> coordinate;
};

#endif
