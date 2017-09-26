#include "AIPlayer.h"
#include "King.h"
#include <fstream>

AIPlayer::AIPlayer(string n, Team t, map<string, tuple<double,double> > probs) : Player(n, t), winProbabilities(probs)
{
}

AIPlayer::~AIPlayer()
{
}

deque<tuple<int,int> > AIPlayer::getMoveInput(Board& b)
{
	// print the board
	b.print();
	
	// prompt the user to enter coordinates
	cout << "\n\n" << name << "'s turn. \n" << endl;	
	
	// the set containing all possible moves
	set<deque<tuple<int,int> > > allAvailableMoves;
	
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
					allAvailableMoves.insert(move);
				}
			}
		}
	}
	
	// pick the move with the highest win ratio
	return getBestMove(allAvailableMoves, b);
}

// returns the move with the highest win ratio
deque<tuple<int,int> > AIPlayer::getBestMove(set<deque<tuple<int,int> > >& allMoves, Board& b)
{
	deque<tuple<int,int> > bestMove;
	double bestWinProbability = -1 * numeric_limits<double>::max();
	
	for (auto move : allMoves) {
		string finalBoardStateAfterMove = getFinalBoardState(move, b);
		
		double thisWinProbability;
		
		// if the AI has never seen this board state
		if (winProbabilities.find(finalBoardStateAfterMove) == winProbabilities.end()) {
			thisWinProbability = .5; 
		} else {
			tuple<double,double> wins = winProbabilities[finalBoardStateAfterMove];
			if (team == red) {
				thisWinProbability = get<0>(wins) / (get<0>(wins) + get<1>(wins));
			} else {
				thisWinProbability = get<1>(wins) / (get<0>(wins) + get<1>(wins));
			}
		}
		
		// if the current move is better
		if (thisWinProbability > bestWinProbability) {
			// update the best so far
			bestWinProbability = thisWinProbability;
			bestMove = move;
		}
	}
	
	return bestMove;
}

string AIPlayer::getFinalBoardState(deque<tuple<int,int> > move, Board& b)
{
	// move to the space and delete all attacked pieces along the way
	tuple<int,int> pieceCoordinates = move.front();
	tuple<int,int> endCoordinates = move.back();
	move.pop_front();
	
	Board bCopy = b.getDeepCopy();
	
	// make the actual move
	bCopy.getTiles()[get<1>(pieceCoordinates)][get<0>(pieceCoordinates)]->getPiece()->move(move);
	
	// change piece to a king if appropriate
	updateToKingIfNeeded(bCopy, endCoordinates);
	
	return bCopy.getBoardString();
}

// update a piece at the given coordinates to a king if needed
void AIPlayer::updateToKingIfNeeded(Board& b, tuple<int,int>& endCoordinates)
{
	int x = get<0>(endCoordinates);
	int y = get<1>(endCoordinates);
	
	// check if piece is not already a king
	if (King* kingCheck = dynamic_cast<King*>(b.getTiles()[y][x]->getPiece())) {
		return;
	}
	
	// change the piece to a king if it has reached the end of the board
	if ((team == red && y == 7) || (team == black && y == 0)) {
		b.getTiles()[y][x]->removePieceFromTile();
		b.getTiles()[y][x]->setPiece(new King(&b, team, endCoordinates));
	}
}

// returns the map of win probabilities
map<string, tuple<double,double> >& AIPlayer::getWinProbabilities()
{
	return winProbabilities;
}

void AIPlayer::writeBoardStatesToFile(bool wonGame)
{
	// open the file
	ofstream output("WinProbabilities.txt");
	
	double valueToAddToRed, valueToAddToBlack;
	if (wonGame) {
		if (team == red) {
			valueToAddToRed = 1;
			valueToAddToBlack = 0;
		} else {
			valueToAddToRed = 0;
			valueToAddToBlack = 1;
		}
	} else {
		if (team == red) {
			valueToAddToRed = 0;
			valueToAddToBlack = 1;
		} else {
			valueToAddToRed = 1;
			valueToAddToBlack = 0;
		}
	}
	
	map<string, tuple<double,double> > winProbabilities;
	
	// add each board state found this game to win probabilites (updated old states when needed)
	for (auto boardState : thisGamesBoardStates) {
		// if the board state has never been seen by the AI before
		if (winProbabilities.find(boardState) == winProbabilities.end()) {
			winProbabilities.insert(make_pair(boardState, make_pair(valueToAddToRed, valueToAddToBlack)));
		} else {
			tuple<double,double> oldValues = winProbabilities.find(boardState)->second;
			double newRedVal = get<0>(oldValues) + valueToAddToRed;
			double newBlackVal = get<1>(oldValues) + valueToAddToBlack;
			winProbabilities[boardState] = make_pair(newRedVal, newBlackVal);
		}
	}
	
	// for each board value in win probabilities
	for (auto group : winProbabilities) {
		output << group.first << " ";
		output << get<0>(group.second) << " " << get<1>(group.second) << endl;
	}
	
	// close the file
	output.close();
}
