#include <iostream>
#include "GameManager.h"
using namespace std;

gameManager::gameManager() {
	score = 0;
}

vector<vector<vector<float>>> gameManager::display() {
	return B.display();
}


bool gameManager::nextTurn() {
	if (!B.contact())
	{
		B.fall();
	}

	if (B.contact()) {
		B.merge();
	}
	score += 10 * B.deleteLine();
	return B.gameOver();
}

void gameManager::onKeyPress(int key = 0) {
	switch (key)
	{
	case 103:
		while (!B.contact())
		{
			B.fall();
		}
		break;
	case 100:
		B.translate(0);
		break;
	case 102:
		B.translate(1);
		break;
	case 101:
		B.rotate();
		break;
	}

	if (B.contact()) {
		B.merge();
	}
	score += 10 * B.deleteLine();
}