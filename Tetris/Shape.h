#pragma once
#include <vector>
using namespace std;

class shape
{
public:
	shape(int type, vector<int> color);
	vector<int> getColor();
	vector<int> getAllPositions();
	void fall();
	void translate(bool direction);
	void rotate();

private:
	int type;
	int rotation;
	int x;
	int y;
	vector<int> color;

};

