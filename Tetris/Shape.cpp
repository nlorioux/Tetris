#include <iostream>
#include "Shape.h"
using namespace std;

#include <cstdlib>
#include <ctime>

const vector<vector<vector<int>>> tableauFormes = {
{{0,0,0,1,1,0,1,1},{0,0,0,1,1,0,1,1},{0,0,0,1,1,0,1,1},{0,0,0,1,1,0,1,1}},
{{0,0,0,1,0,2,0,3},{-1,1,0,1,1,1,2,1},{0,0,0,1,0,2,0,3},{-1,1,0,1,1,1,2,1}},
{{-1,-1,0,-1,0,0,0,1},{-1,0,-1,1,0,0,1,0},{0,-1,0,0,0,1,1,1},{-1,0,0,0,1,0,1,-1}},
{{-1,-1,0,-1,0,0,1,0},{-1,1,-1,0,0,0,0,-1},{-1,-1,0,-1,0,0,1,0},{-1,1,-1,0,0,0,0,-1}},
{{-1,0,0,0,0,-1,1,-1},{-1,-1,-1,0,0,0,0,1},{-1,0,0,0,0,-1,1,-1},{-1,-1,-1,0,0,0,0,1}},
{{0,-1,1,-1,0,0,0,1},{-1,-1,-1,0,0,0,1,0},{0,-1,0,0,0,1,-1,1},{-1,0,0,0,1,0,1,1}},
{{-1,0,0,0,1,0,0,1},{0,-1,0,0,0,1,1,0},{-1,0,0,0,0,-1,1,0},{-1,0,0,0,0,-1,0,1}}
};

shape::shape() {
	type = 0;
	rotation = 0;
	x = 0;
	y = 0;
	color = { 0,0,0 };
}

shape::shape(int t, vector<float> c) {
	type = t;
	rotation = rand() % 4;
	x = rand() % 4+3;
	y = 19;
	color = c;
}

vector<float> shape::getColor() {
	return color;
}

vector<int> shape::getAllPositions() {
	vector<int> pos;
	pos.push_back(tableauFormes[type][rotation][0]+x);
	pos.push_back(tableauFormes[type][rotation][1]+y);
	pos.push_back(tableauFormes[type][rotation][2]+x);
	pos.push_back(tableauFormes[type][rotation][3]+y);
	pos.push_back(tableauFormes[type][rotation][4]+x);
	pos.push_back(tableauFormes[type][rotation][5]+y);
	pos.push_back(tableauFormes[type][rotation][6]+x);
	pos.push_back(tableauFormes[type][rotation][7]+y);
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