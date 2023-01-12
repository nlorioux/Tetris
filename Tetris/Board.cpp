#include <iostream>
#include "Board.h"
#include "TableauForme.h"
using namespace std;

#include <cstdlib>
#include <ctime>

board::board() {
	srand(time(NULL));
	int type = rand() % 7;
	float r, g, b;
	vector<float> color;
	color.push_back(r);
	color.push_back(g);
	color.push_back(b);
	currentShape = shape(type, color);
}

void board::deleteLineByID(int k) {
	for (int j = k; j < 20; j++) {
		if (j != 0) {
			for (int i = 0; i < 10; i++) {
				grid[i][j - 1][0] = grid[i][j][0];
				grid[i][j - 1][1] = grid[i][j][1];
				grid[i][j - 1][2] = grid[i][j][2];
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		grid[i][19][0] = 0;
		grid[i][19][1] = 0;
		grid[i][19][2] = 0;
	}
}

int board::deleteLine() {
	bool fullLine = true;
	vector<int> deletedLines;
	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < 10; i++) {
			if (grid[i][j][0] == 0 && grid[i][j][1] == 0 && grid[i][j][2] == 0) {
				fullLine = false;
			}
			if (fullLine && j == 19) {
				deletedLines.push_back(j);
			}
			
		}
	}
	for (int j = deletedLines.size() - j; j > 0; j--) {
		deleteLineByID(j);
	}
}

shape board::getCurrentShape() {
	return currentShape;
}

void board::setCurrentShape(shape S) {
	currentShape = S;
}

void board::fall() {
	shape test;
	test = currentShape;
	test.setY(test.getY() - 1);
	bool capasse = true;
	vector<int> pos = test.getAllPositions();
	if (pos.size() == 8) {
		for (int i = 0; i < 4; i++) {
			int x = pos[i * 2];
			int y = pos[i * 2 + 1];
			if (grid[x][y][0] != 0 || grid[x][y][1] != 0 || grid[x][y][2] != 0) {
				capasse = false;
			}
		}
		if (capasse) {
			currentShape.setY(currentShape.getY() - 1);
		}
		else {
			merge();
		}
	}
}

void board::translate(bool direction) {
	shape test;
	test = currentShape;
	bool capasse = true;
	if (direction == 0) {
		test.setX(test.getX() - 1);
	}
	else {
		test.setX(test.getX() + 1);
	}
	vector<int> pos = test.getAllPositions();
	if (pos.size() == 8) {
		for (int i = 0; i < 4; i++) {
			int x = pos[i * 2];
			int y = pos[i * 2 + 1];
			if (x < 0 || x>9 || grid[x][y][0] != 0 || grid[x][y][1] != 0 || grid[x][y][2] != 0) {
				capasse = false;
			}
		}
		if (capasse) {
			currentShape.setX(test.getX());
		}
	}
}

void board::rotate() {
	shape test;
	test = currentShape;
	bool capasse = true;
	test.tourne();
	vector<int> pos = test.getAllPositions();
	if (pos.size() == 8) {
		for (int i = 0; i < 4; i++) {
			int x = pos[i * 2];
			int y = pos[i * 2 + 1];
			if (x < 0 || x>9 || grid[x][y][0] != 0 || grid[x][y][1] != 0 || grid[x][y][2] != 0) {
				capasse = false;
			}
		}
		if (capasse) {
			currentShape.tourne();
		}
	}
}