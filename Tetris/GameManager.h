#pragma once
#include "Board.h"

class gameManager
{
public:
	gameManager();

	int score;
	bool nextTurn();
	void onKeyPress(int);
	vector<vector<vector<float>>> display();
private:
	board B;
};

