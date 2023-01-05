#include <iostream>
#include "Board.h"
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
	if (grid[test.getX()][test.getY()][0] == 0 && grid[test.getX()][test.getY()][1] == 0 && grid[test.getX()][test.getY()][2] == 0) {
		currentShape.setY(currentShape.getY() - 1);
	}
	else {
		merge();
	}
}

void board::translate(bool direction) {

}

void board::rotate() {

}