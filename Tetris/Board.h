#pragma once
#include "Shape.h"

class board
{
public:
	board();
	vector<vector<vector<float>>> display();
	bool contact();
	void merge();
	void deleteLine();
	shape getCurrentShape();
	void setCurrentShape(shape S);
	void fall();
	void translate(bool direction); //0 gauche
	void rotate();
private:
	float grid[10][20][3];
	shape currentShape;
	void deleteLineByID(int k);
};


