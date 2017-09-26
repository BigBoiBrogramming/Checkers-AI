#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <deque>
#include <map>
#include "Board.h"
#include "Team.h"

using namespace std;

class Player {
public:
	Player();
	Player(string n, Team t);
	virtual ~Player();
	string getName();
	Team getTeam();
	int getPiecesRemaining();
	void decrementPiecesRemaining();
	virtual deque<tuple<int,int> > getMoveInput(Board& b);
	virtual void writeBoardStatesToFile(bool wonGame);
	set<string>& getThisGamesBoardStates();
	
protected:
	map<int, deque<tuple<int,int> > > displayMovesAndReturnMap(set<deque<tuple<int,int> > >& availableMoves);
	int getMoveNumber(int numMoves);
	set<deque<tuple<int,int> > > selectPieceAndGetMoves(Board& board, Player* player);
	void inputCoordinates(int& x, int& y, Board& board, Team team);
	// a set of strings containing all board states from the current game
	set<string> thisGamesBoardStates;
	
	string name;
	Team team;
	int piecesRemaining;
};

#endif
