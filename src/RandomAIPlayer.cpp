#include "RandomAIPlayer.h"
#include <vector>

RandomAIPlayer::RandomAIPlayer(string n, Team t, map<string, tuple<double,double> > probs) : AIPlayer(n, t, probs)
{
}

RandomAIPlayer::~RandomAIPlayer()
{
}

deque<tuple<int,int> > RandomAIPlayer::getMoveInput(Board& b)
{
	// print the board
	b.print();
	
	// prompt the user to enter coordinates
	cout << "\n\n" << name << "'s turn. \n" << endl;	
	
	// the list containing all possible moves
	vector<deque<tuple<int,int> > > allAvailableMoves;
	
	// get available moves for each friendly piece
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece* currentPiece = NULL;
			if (b.getTiles()[j][i]->hasPieceOnTile()) {
				currentPiece = b.getTiles()[j][i]->getPiece();
			}
			
			// if the current piece exists and is friendly
			if (currentPiece != NULL && currentPiece->getTeam() == team) {
				// get its available moves
				set<deque<tuple<int,int> > > moves = currentPiece->getAvailableMoves();
				
				// add each of the available moves to the set of all available moves
				for (auto move : moves) {
					allAvailableMoves.push_back(move);
				}
			}
		}
	}
	
	// return a random available move
	return allAvailableMoves[rand() % allAvailableMoves.size()];
}
