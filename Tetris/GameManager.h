#pragma once
#include "Board.h"

class gameManager
{
public:
	gameManager();
	bool getNewShapeSpawned() { return newShapeSpawned };
	void setNewShapeSpawned(bool change) { newShapeSpawned = change; };
	void nextTurn();
	void onKeyPress(int);
	vector<vector<vector<float>>> display();
private:
	board B;
	int score;
	bool newShapeSpawned = false;
};

