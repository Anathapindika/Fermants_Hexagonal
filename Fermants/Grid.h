#pragma once
#include <string>
using namespace std;

class Grid
{

	friend class Ant;

public:
	Grid(int gridg, int nduststep, int startx, int starty, int foodx, int foody);
	void dGrid();
	

	void accumulateGrids();
	void printGrid(string path);
	void Grid::dust(int duststep);

	int gridg;
	int nduststep;
	int duststep;
	int startx;
	int starty;
	int foodx;
	int foody;


	float** field;
	float** f0f;
	float** f0nf;
	float** f0t;
	float*** df0;

	float** f1f;
	float** f1nf;
	float** f1t;
	float*** df1;

	float** f2f;
	float** f2nf;
	float** f2t;
	float*** df2;

	float** f3f;
	float** f3nf;
	float** f3t;
	float*** df3;

	float** f4f;
	float** f4nf;
	float** f4t;
	float*** df4;

	float** f5f;
	float** f5nf;
	float** f5t;
	float*** df5;
};

