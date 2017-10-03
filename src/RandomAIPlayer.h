#ifndef RANDOMAIPLAYER_H
#define RANDOMAIPLAYER_H

#include "AIPlayer.h"
#include <map>
#include <set>

using namespace std;

class RandomAIPlayer : public AIPlayer {
public:
	RandomAIPlayer(string n, Team t, map<string, tuple<double,double> > winProbabilities);
	~RandomAIPlayer();
	deque<tuple<int,int> > getMoveInput(Board& b);
};

#endif
