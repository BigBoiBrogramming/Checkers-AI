#include "Piece.h"

Piece::Piece(Board* board, Team team)
{
	// initialize here
	boardPtr_ = board;
	teamOfPiece_ = team;
	tileLocationOfPiece_ = NULL;
}

ostream& operator<<(ostream& os, const Piece& p)
{
	string color;
	if (p.team == Team::red) {
		color = "R";
	} else {
		color = "B";
	}
	
	os << "n" << color;
	
	return os;
}
set<deque<tuple<int,int> > > Piece::getAvailableAttacks(tuple<int,int> coord) {


	set<tuple<int,int> > possiblePathStarters;
	
	// intialize the "forward" direction, and corrdinate bound thereof	
	int moveDirection;
	int maxY;
	
	// if the team is red, you move up 2 and your bound in 7
	// otherwise, you move down 2 and your bound is 0
	if (teamOfPiece_ == Team::Red) 
	{
		moveDirection = 2;
		maxY = 7;
		
	}
	else 
	{
		moveDirection = -2;
		maxY = 0;
	}
	
	
	
	// we have a normal piece, so we can only move in a single
	// direction along y
	int testY = get<1>(coord) + moveDirection;
	
	// there is always the possibility to move along x
	// positively or negatively
	int test1X = get<0>(coord) + 2;
	int test2X = get<0>(coord) - 2;
	
	// if we have no reached the barrier of moving along y,
	// we can check our x options
	if (testY <= maxY) 
	{
		
		if ( test1X <= 7 
		&& !(boardPtr_->tiles[test1X][testY]->isPieceOnTile()) 
		&& (boardPtr_->tiles[test1X - 1][testY - 1]->getTeamOfPieceOnTile() != teamOfPiece_)) 
		{
			possiblePathStarters.insert( (test1X, testY) );
		}
		
		if ( test2X >= 0
		&& !(boardPtr_->tiles[test2X][testY]->isPieceOnTile())  
		&& (boardPtr_->tiles[test2X - 1][testY - 1]->getTeamOfPieceOnTile() != teamOfPiece_))
		{
			possiblePathStarters.insert( (test2X, testY) );
		}
		
	}
		
	
	
	// declare our set of attack chains that will eventually be returned	
	set<stack<tuple<int,int> > > possibleAttackChains;
	
	
	
	
	for(auto firstStepCoord : possiblePathStarters) {
		
		// recursive call to create chains of steps after moving to firstStepCoord
		set<stack<tuple<int,int> > > chainsAfterFirstStep = getAvailableAttacks(firstStepCoord);
		
		// go through chains and add on the first step
		for(auto chain: chainsAfterFirstStep) {
			
			stack<tuple<int,int> chainCopy = chain.copy();
			
			chainCopy.push_front(firstStepCoord);
			
			possibleAttackChains.insert(chainCopy);
			
			
		}
		
		// add on smallest chain, our first step, to attack chains
		stack<tuple<int,int> > smallestChain = { firstStepCoord };
		possibleAttackChains.insert(smallestChain);
		
		
		return possibleAttackChains
		
		
	}
			
	
}


set<stack<tuple<int,int> > > Piece::getAvailableMoves() 
{
	
	set<tuple<int,int> > possibleCoordsToMoveTo;
	
	int moveDirection;
	int maxY;
	
	if (teamOfPiece_ == Team.Red) 
	{
		moveDirection = 1;
		maxY = 7;
		
	}
	else 
	{
		moveDirection = -1;
		maxY = 0;
	}
	
	
	
	int test1X = get<0>(coordinates_) + 1;
	int testY = get<1>(coordinates_) + moveDirection;
	
	
	int test2X = get<0>(coordinates_) - 1;
	
	
	if (testY <= maxY) {
		
		if ( test1X <= 7 &&  !(boardPtr_->tiles[test1X][testY]->isPieceOnTile())  ) {
			
			stack<tuple<int,int> > move = {(test1X, testY)};
			
			possibleCoordsToMoveTo.insert(move);
		}
		
		if ( test2X >= 0  &&  !(boardPtr_->tiles[test2X][testY]->isPieceOnTile())  ) {
			
			stack<tuple<int,int> > move = {(test2X, testY)};
			
			possibleCoordsToMoveTo.insert(move);
		}
		
	}
	
	
	
	set<stack<tuple<int,int> > > possibleAttacks = getAvailableAttacks( );
	
	
	
	
	
	
}

void Piece::move(int rowCoord, int columnCorrd) {
	
	// things to check...
		// is the space available to be moved to
			// conditions:
				// must be within (0...7,0...7)
				// must be empty
				// if on red team, must be (+1, +1) or (-1, +1)
				// if an enemy piece exists on (+1, +1) or (-1, +1), move to (+2, +2) or (-2, +2), respectively
				
				
	
				
	
	if ( !(endTile->isPieceOnTile()) ) {
		tileLocationOfPiece_ = Tile
		
	}
	else {
		cerr << "there is already a tile here";
	}
	
}
