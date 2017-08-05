#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool inputPlayerType(int playerNumber)
{
	string answer;
	cout << "Would you like player " << playerNumber << " to be AI (y/n): ";
	while (answer != "y" && answer != "n") {
		cin >> answer;
		transform(answer.begin(), answer.end(), answer.begin(),::tolower);
		if (answer != "y" && answer != "n") {
			cout << "Enter either 'y' or 'n': ";
		}
	}
	
	return answer == "y";
}

string inputName()
{
	cout << "Enter the player's name: ";
	cin.ignore();
	string name;
	getline(cin, name);
	return name;
}

#endif
