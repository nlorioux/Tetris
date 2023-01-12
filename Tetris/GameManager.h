#pragma once
#include "Board.h"

class gameManager
{
public:
	gameManager();

	void nextTurn(int);
	vector<vector<vector<float>>> display();

	void nextTurn(int);

private:
	board B;
	int score;
};

