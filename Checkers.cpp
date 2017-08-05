#include "src/Game.h"
#include "src/Player.h"
#include "src/Board.h"

using namespace std;

bool inputPlayerType(int playerNumber);
void inputName(Player& p);

int main(int argc, char *argv[])
{
	Board board = Board();
	
	bool player1IsAI = inputPlayerType(1);
	if (player1IsAI) {
		cout << "AI for this program is not yet supported. Exiting program." << endl;
		exit(1);
	}
	Player* player1;
	if (!player1IsAI) {
		string name = inputName();
		player1 = new Player(1, name);
	} else {
		// initialize player1 as AI 
	}
	
	bool player2IsAI = inputPlayerType(2);
	if (player2IsAI) {
		cout << "AI for this program is not yet supported. Exiting program." << endl;
		exit(1);
	}
	Player* player2;
	if (!player2IsAI) {
		string name = inputName();
		player2 = new Player(2, name);
	} else {
		// initialize player1 as AI 
	}
	
	
	cout << "Player " << player1->getPlayerNumber() << "'s name is " << player1->getName() << "." << endl;
	cout << "Player " << player2->getPlayerNumber() << "'s name is " << player2->getName() << "." << endl;
}