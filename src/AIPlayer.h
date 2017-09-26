#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"
#include <map>
#include <set>

using namespace std;

class AIPlayer : public Player {
public:
	AIPlayer(string n, Team t, map<string, tuple<double,double> > winProbabilities);
	~AIPlayer();
	deque<tuple<int,int> > getMoveInput(Board& b);
	void writeBoardStatesToFile(bool wonGame);
	
private:
	map<string, tuple<double,double> > getWinProbabilities();
	deque<tuple<int,int> > getBestMove(set<deque<tuple<int,int> > >& allMoves, Board& b);
	string getFinalBoardState(deque<tuple<int,int> > move, Board& b);
	void updateToKingIfNeeded(Board& b, tuple<int,int>& endCoordinates);
	
	// a map with keys of board states and values of tuples containing the number of red wins and black wins
	map<string, tuple<double,double> > winProbabilities;
};

#endif
