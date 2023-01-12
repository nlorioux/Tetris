#include <iostream>
#include "GameManager.h"
using namespace std;

gameManager::gameManager() {
	B = board();
	score = 0;
}

vector<vector<vector<float>>> gameManager::display() {
	return board.display();
}