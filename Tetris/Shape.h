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
	void setX(int a);
	void setY(int b);
	void tourne();
	int getX();
	int getY();

private:
	int type;
	int rotation;
	int x;
	int y;
	vector<float> color;
};

