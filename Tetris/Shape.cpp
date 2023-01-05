#include <iostream>
#include "Shape.h"
using namespace std;

#include <cstdlib>
#include <ctime>

shape::shape() {
	type = 0;
	rotation = 0;
	x = 0;
	y = 0;
	color = { 0,0,0 };
}

shape::shape(int t, vector<float> c) {
	srand(time(NULL));
	type = t;
	rotation = rand() % 4;
	x = rand() % 10;
	y = 19;
	color = c;
}

vector<float> shape::getColor() {
	return color;
}

vector<int> shape::getAllPositions() {
	vector<int> pos;
	pos.push_back(x);
	pos.push_back(y);
	return pos;
}

void shape::setX(int a) {
	x = a;
}

void shape::setY(int b) {
	y = b;
}

void shape::tourne() {
	rotation += 1;
	if (rotation == 4) {
		rotation = 0;
	}
}

int shape::getX() { return x; }
int shape::getY() { return y; }