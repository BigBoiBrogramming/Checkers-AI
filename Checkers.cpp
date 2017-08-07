#include "src/Game.h"
#include "src/Player.h"
#include "src/Board.h"

using namespace std;

bool inputPlayerType(int playerNumber);
void inputName(Player& p);

int main(int argc, char *argv[])
{
	Board board = Board();
	
	// set up Player 1
	bool redPlayerIsAI = inputPlayerType(1);
	if (redPlayerIsAI) {
		cout << "AI for this program is not yet supported. Exiting program." << endl;
		exit(1);
	}
	Player* redPlayer;
	if (!redPlayerIsAI) {
		string name = inputName();
		redPlayer = new Player(1, name, red);
	} else {
		// initialize Player 1 as AI 
	}
	
	// set up Player 2
	bool blackPlayerIsAI = inputPlayerType(2);
	if (blackPlayerIsAI) {
		cout << "AI for this program is not yet supported. Exiting program." << endl;
		exit(1);
	}
	Player* blackPlayer;
	if (!blackPlayerIsAI) {
		string name = inputName();
		blackPlayer = new Player(2, name, black);
	} else {
		// initialize Player 2 as AI 
	}
	
	cout << endl;
	
	// create an array of the two players
	Player* players[] = {redPlayer, blackPlayer};
	string teams[] = {"Red", "Black"};
	
	// play the game until one player runs out of pieces
	while (redPlayer->getPiecesRemaining() > 0 && blackPlayer->getPiecesRemaining() > 0) {
		for (auto player : players) {
			// print the board
			board.print();
			
			// prompt the user to enter coordinates
			cout << endl << teams[player->getTeam()] << " Player's turn. ";
			cout << "Select coordinates of a friendly piece (x y) to see available moves: ";
			int x, y;
			
			inputCoordinates(x, y, board, player->getTeam());
			
			set<deque<tuple<int,int> > > availableMoves = board.getTiles()[y][x]->getPiece()->getAvailableMoves();
			
			cout << "Enter the coordinates that you would like to move to: ";
			int moveX, moveY;
			cin >> moveX >> moveY;
			board.getTiles()[y][x]->getPiece()->move(make_tuple(moveX, moveY));
		}
	}
	
	// deallocate players
	delete redPlayer;
	delete blackPlayer;
}