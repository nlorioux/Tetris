#pragma once
#include "Board.h"

class gameManager
{
public:
	gameManager();
	void nextTurn();

private:
	board B;
	int score;
};

