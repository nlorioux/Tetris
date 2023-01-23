#pragma once
#include "Board.h"

class gameManager
{
public:
	gameManager();
	int score;
	bool nextTurn(int);
	vector<vector<vector<float>>> display();
private:
	board B;
};

