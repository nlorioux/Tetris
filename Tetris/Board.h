#pragma once
# include "Shape.h"
class board
{
public:
	board();
	void display();
	bool contact();
	void merge();
	int deleteLine();
	shape getCurrentShape();
	void setCurrentShape(shape S);

private:
	int grid[10][30][3];
	shape currentShape;
};


