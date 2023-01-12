#pragma once
#include "Board.h"

class gameManager
{
public:
	gameManager();
	void nextTurn(int);

private:
	board B;
	int score;
};

