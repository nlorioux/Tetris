#pragma once
#include "Board.h"

class gameManager
{
public:
	gameManager();
	void nextTurn();
	vector<vector<vector<float>>> display();
private:
	board B;
	int score;
};

