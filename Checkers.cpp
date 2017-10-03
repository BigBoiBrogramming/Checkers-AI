#include <map>
#include "src/Game.h"
#include "src/Player.h"
#include "src/AIPlayer.h"
#include "src/RandomAIPlayer.h"
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	Board board = Board();
	
	// retrieve the key of win probabilities
	map<string, tuple<double,double> > winProbabilities;
	ifstream infile("WinProbabilities.txt");
	
	cout << "Loading in training data. This may take a few of minutes..." << endl;
	
	// add in each line of existing data
	string boardstate;
	int redWins, blackWins;
	
	while (infile >> boardstate >> redWins >> blackWins)
	{
		winProbabilities.insert(make_pair(boardstate, make_pair(redWins, blackWins)));
	}
	infile.close();
	
	cout << winProbabilities.size() << " units of training data were successfully loaded!\n" << endl;
	
	// set up Player 1
	bool redPlayerIsAI = inputPlayerType(1);
	Player* redPlayer;
	if (!redPlayerIsAI) {
		string name = inputName();
		redPlayer = new Player(name, red);
	} else {
		cout << "Creating Player 1 AI..." << endl;
		redPlayer = new AIPlayer("Player 1 (AI)", red, winProbabilities);
	}
	
	// set up Player 2
	bool blackPlayerIsAI = inputPlayerType(2);
	Player* blackPlayer;
	if (!blackPlayerIsAI) {
		string name = inputName();
		blackPlayer = new Player(name, black);
	} else {
	cout << "Creating Player 2 AI..." << endl;
		blackPlayer = new AIPlayer("Player 2 (AI)", black, winProbabilities);
	}
	
	cout << endl;
	
	// create an array of the two players
	Player* players[] = {redPlayer, blackPlayer};
	
	// play the game until one player runs out of pieces
	while (redPlayer->getPiecesRemaining() > 0 && blackPlayer->getPiecesRemaining() > 0) {
		// for each of the players
		for (int i = 0; i < 2; i++) {
			cout << endl;
			Player* currentPlayer = players[i];
			Player* enemyPlayer = players[!i];
			
			deque<tuple<int,int> > finalMove = currentPlayer->getMoveInput(board);
			
			// check to see if no moves are available
			if (finalMove.size() == 0) {
				cout << currentPlayer->getName() << " has no available moves.";
				cout << " The result of the game is a draw!" << endl;
				delete redPlayer;
				delete blackPlayer;
				exit(0);
			}
			
			// move to the space and delete all attacked pieces along the way
			tuple<int,int> pieceCoordinates = finalMove.front();
			tuple<int,int> endCoordinates = finalMove.back();
			finalMove.pop_front();
			int numCaptured = board.getTiles()[get<1>(pieceCoordinates)][get<0>(pieceCoordinates)]->getPiece()->move(finalMove);
			
			// change piece to a king if appropriate
			updateToKingIfNeeded(board, endCoordinates, currentPlayer->getTeam());
			
			// add the updated board state to each AI
			currentPlayer->getThisGamesBoardStates().insert(board.getBoardString());
			enemyPlayer->getThisGamesBoardStates().insert(board.getBoardString());
			
			// update enemy player's piecesRemaining count
			for (int j = 0; j < numCaptured; j++) {
				enemyPlayer->decrementPiecesRemaining();
			}
			
			// break if the enemy has no more pieces
			if (enemyPlayer->getPiecesRemaining() == 0) {
				break;
			}
		}
	}
	
	cout << "\n" << endl;
	
	bool player1Wins;
	
	// determine winner
	if (players[1]->getPiecesRemaining() == 0) {
		cout << players[0]->getName();
		player1Wins = true;
	} else {
		player1Wins = false;
		cout << players[1]->getName();
	}
	cout << " wins!\n" << endl;
	
	board.print();
	
	cout << "\n\nSaving data to output file..." << endl;
	
	// write the board states to the data file
	// if player one is AI
	if (AIPlayer* aiCheck = dynamic_cast<AIPlayer*>(players[0])) {
		players[0]->writeBoardStatesToFile(player1Wins);
	} else {
		// if player two is AI
		if (AIPlayer* aiCheck = dynamic_cast<AIPlayer*>(players[1])) {
			players[1]->writeBoardStatesToFile(!player1Wins);
		}
	}
	
	// deallocate players
	delete redPlayer;
	delete blackPlayer;
}
