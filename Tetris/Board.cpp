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
	r = (rand() % 100 +1) / 100;
	g = (rand() % 100 + 1) / 100;
	b = (rand() % 100 + 1) / 100;
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

bool board::contact() {
	bool contact = false;
	vector<int> pos = currentShape.getAllPositions();
	if (pos.size() == 8) {
		for (int i = 0; i < 4; i++) {
			int x = pos[i * 2];
			int y = pos[i * 2 + 1];
			if (grid[x][y-1][0] != 0 || grid[x][y-1][1] != 0 || grid[x][y-1][2] != 0) {
				contact = true;
			}
		}
	}
	return contact;
}

void board::merge() {
	vector<int> pos = currentShape.getAllPositions();
	if (pos.size() == 8) {
		for (int i = 0; i < 4; i++) {
			int x = pos[i * 2];
			int y = pos[i * 2 + 1];
			if (currentShape.getColor().size() == 3) {
				grid[x][y] = { currentShape.getColor[0],currentShape.getColor[1],currentShape.getColor[2] }
			}
		}
	}
	int type = rand() % 7;
	float r, g, b;
	r = (rand() % 100 + 1) / 100;
	g = (rand() % 100 + 1) / 100;
	b = (rand() % 100 + 1) / 100;
	vector<float> color;
	color.push_back(r);
	color.push_back(g);
	color.push_back(b);
	currentShape = new shape(type, color);

}


vector<vector<vector<float>>> board::display() {
	vector<vector<vector<float>>> toDisplay;

	for (int x = 0; x < 10; x++) {
		vector<vector<float>> colone = new vector<vector<float>>;
		for (int y = 0; y <20; y++) {
			vector<float> color = new vector<float>;
			for (int c = 0; c < 3; c++) {
				color.push_back(grid[x][y][c]);
			}
			colone.push_back(color);
		}
		toDisplay.push_back(colone);
	}
	return toDisplay;
}