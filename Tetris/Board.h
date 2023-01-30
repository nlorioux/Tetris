#pragma once
#include "Shape.h"

class board
{
public:
	board();
	/// <summary>
	/// Method that displays the board.
	/// </summary>
	/// <returns>Returns the board as a matrix (vector of vectors) of colors.</returns>
	vector<vector<vector<float>>> display();

	/// <summary>
	/// Method that checks if there is a contact between the current shape and the rest of the board. 
	/// </summary>
	/// <returns>Returns true if there is a contact, false otherwise.</returns>
	bool contact();

	/// <summary>
	/// Method that merges the current shape with the board.
	/// </summary>
	void merge();

	/// <summary>
	/// Method that deletes lines when they are full, can delete multiple lines at the same time.
	/// </summary>
	/// <returns>Returns the number of deleted lines.</returns>
	int deleteLine();
	shape getCurrentShape();
	void setCurrentShape(shape S);
	void fall();
	void translate(bool direction); //0 gauche
	void rotate();
	bool gameOver();
private:
	float grid[10][20][3];
	shape currentShape;
	void deleteLineByID(int k);
};


