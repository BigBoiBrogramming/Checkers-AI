#include "King.h"

King::King(Board* board, Team team, tuple<int,int> coordinate) : Piece (board, team, coordinate)
{
}

// returns the set of single square moves
set<deque<tuple<int,int> > > King::getAvailableSingleSquareMoves(tuple<int,int>& currentCoord)
{
	// the set of single moves that gets returned
	set<deque<tuple<int,int> > > availableSingleMoves;
	
	// iterate through both possible directions
	for (int i = 0; i < 2; i++) {
		// intialize the forward direction and coordinate bound
		int moveDirection;
		int maxY;
		
		// for one direction, move up 1 and bound is 7
		// for the other, move down 1 and bound is 0
		if (i == 0) {
			moveDirection = 1;
			maxY = 7;
		} else {
			moveDirection = -1;
			maxY = 0;
		}
		
		// y coordinate of attempted diagonal moves
		int attemptY = get<1>(coordinate) + moveDirection;
		
		// x coordinates of attempted diagonal moves
		int attempt1X = get<0>(coordinate) + 1;
		int attempt2X = get<0>(coordinate) - 1;
		
		// check if attack move is in bounds on the y-axis
		if (attemptY <= maxY) {
			// check if right side move is valid
			if (attempt1X <= 7 && !(board->getTiles()[attemptY][attempt1X]->hasPieceOnTile())) {
				// add the right side move to the set of available moves
				deque<tuple<int,int> > move;
				move.push(make_tuple(attempt1X, attemptY));
				availableSingleMoves.insert(move);
			}
			// check if left side move is valid
			if (attempt2X >= 0 && !(board->getTiles()[attemptY][attempt2X]->hasPieceOnTile())) {
				// add the left side move to the set of available moves
				deque<tuple<int,int> > move;
				move.push(make_tuple(attempt2X, attemptY));
				availableSingleMoves.insert(move);
			}
		}
	}
	
	return availableSingleMoves;
}

// returns the set of attack moves
set<deque<tuple<int,int> > > King::getAvailableAttacks(tuple<int,int>& currentCoord)
{
	// the set of attack chains that gets returned
	set<deque<tuple<int,int> > > possibleAttackChains;
	
	// iterate through both possible directions
	for (int i = 0; i < 2; i++) {
		// a set containing coordinate of the first moves in leap chains
		set<tuple<int,int> > possiblePathStarters;
		
		// intialize the forward direction and coordinate bound
		int moveDirection;
		int maxY;
		
		// for one direction, move up 2 and bound is 7
		// for the other, move down 2 and bound is 0
		if (i == 0) {
			moveDirection = 2;
			maxY = 7;
			
		} else {
			moveDirection = -2;
			maxY = 0;
		}
		
		// y coordinate of attempted attacks (position after jumping)
		int attemptY = get<1>(currentCoord) + moveDirection;
		
		// x coordinates of attempted attacks (position after jumping)
		int attempt1X = get<0>(currentCoord) + 2;
		int attempt2X = get<0>(currentCoord) - 2;
		
		// check if attack move is in bounds on the y-axis
		if (attemptY <= maxY) {
			// check if right side attack move is valid
			if ( attempt1X <= 7 
			&& !(board->getTiles()[attemptY][attempt1X]->hasPieceOnTile()) 
			&& (board->getTiles()[attemptY - (moveDirection/2)][attempt1X - (moveDirection/2)]->getPiece()->getTeam() != team)) 
			{
				// add the right side attack coordinate to the set of possible path starters
				possiblePathStarters.insert(make_tuple(attempt1X, attemptY));
			}
			// check if left side attack move is valid
			if ( attempt2X >= 0
			&& !(board->getTiles()[attemptY][attempt2X]->hasPieceOnTile())  
			&& (board->getTiles()[attemptY - (moveDirection/2)][attempt2X - (moveDirection/2)]->getPiece()->getTeam() != team))
			{
				// add the left side attack coordinate to the set of possible path starters
				possiblePathStarters.insert(make_tuple(attempt2X, attemptY));
			}
		}
		
		// iterate through the coordinates of path starters
		for(auto firstStepCoord : possiblePathStarters) {
			// recursive call to generate all chains of steps after moving to the first step
			set<deque<tuple<int,int> > > chainsAfterFirstStep = getAvailableAttacks(firstStepCoord);
			
			// iterate through chains and add the first step onto the attack chains
			for(auto chain : chainsAfterFirstStep) {
				chain.push(firstStepCoord);
				possibleAttackChains.insert(chain);
			}
			
			// create the smallest possible chain that consists of only the first step
			deque<tuple<int,int> > smallestChain;
			smallestChain.push(firstStepCoord);
			possibleAttackChains.insert(smallestChain);
		}
	}
		
	return possibleAttackChains;
}

// print the piece
ostream& operator<<(ostream& os, const King& k)
{
	string color;
	if (k.team == Team::red) {
		color = "R";
	} else {
		color = "B";
	}
	
	os << "k" << color;
	
	return os;
}
