#include <iostream>
#include "GameManager.h"
using namespace std;

gameManager::gameManager() {
	score = 0;
}

vector<vector<vector<float>>> gameManager::display() {
	return B.display();
}

bool gameManager::nextTurn(int key = 0) {
	int scorePlus = 0;
	switch (key)
	{
	case 1:
		while (!B.contact())
		{
			B.fall();
		}
		break;
	case 2:
		B.translate(0);
		break;
	case 3:
		B.translate(1);
		break;
	case 4:
		B.rotate();
		break;
	}

	if (!B.contact())
	{
		B.fall();
	}

	if (B.contact()) {
		B.merge();
		score += 10*B.deleteLine();
	}
	return B.gameOver();
}