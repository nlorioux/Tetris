#pragma once
#include <vector>
using namespace std;

class shape
{
public:
	shape();
	shape(int type, vector<float> color);
	vector<float> getColor();
	vector<int> getAllPositions();
	void fall();
	void translate(bool direction);
	void rotate();

private:
	int type;
	int rotation;
	int x;
	int y;
	vector<float> color;

};

