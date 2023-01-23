#pragma once
#include "Board.h"

class gameManager
{
public:
	gameManager();

	int score;
	bool nextTurn();
	bool getNewShapeSpawned() { return newShapeSpawned };
	void setNewShapeSpawned(bool change) { newShapeSpawned = change; };
	void onKeyPress(int);
	vector<vector<vector<float>>> display();
private:
	board B;
	bool newShapeSpawned = false;
};

