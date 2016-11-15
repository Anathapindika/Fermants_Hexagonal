#include "stdafx.h"
#include "Grid.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


Grid::Grid(int gridg, int nduststep, int startx, int starty, int foodx, int foody)
{
	this->gridg = gridg;
	this->nduststep = nduststep;
	this->duststep = 0;
	this->startx = startx;
	this->starty = starty;
	this->foodx = foodx;
	this->foody = foody;
	
												//Initialization of the Grid - it counts the ants,
	field = new float*[gridg];						//where they are
	for (int i = 0; i<gridg; i++)
		field[i] = new float[gridg];
	//memset(field, 0, sizeof(field));

	f0f = new float*[gridg];							//where they move in direction 0
	for (int i = 0; i<gridg; i++)
		f0f[i] = new float[gridg];
	//memset(f0, 0, sizeof(f0));

	f1f = new float*[gridg];							//where they move in direction 1
	for (int i = 0; i<gridg; i++)
		f1f[i] = new float[gridg];

	f2f = new float*[gridg];							//where they move in direction 2
	for (int i = 0; i<gridg; i++)
		f2f[i] = new float[gridg];

	f3f = new float*[gridg];							//where they move in direction 3
	for (int i = 0; i<gridg; i++)
		f3f[i] = new float[gridg];

	f4f = new float*[gridg];							//where they move in direction 4
	for (int i = 0; i<gridg; i++)
		f4f[i] = new float[gridg];

	f5f = new float*[gridg];							//where they move in direction 5
	for (int i = 0; i<gridg; i++)
		f5f[i] = new float[gridg];



	f0nf = new float*[gridg];							//where they move in direction 0
	for (int i = 0; i<gridg; i++)
		f0nf[i] = new float[gridg];
	//memset(f0, 0, sizeof(f0));

	f1nf = new float*[gridg];							//where they move in direction 1
	for (int i = 0; i<gridg; i++)
		f1nf[i] = new float[gridg];

	f2nf = new float*[gridg];							//where they move in direction 2
	for (int i = 0; i<gridg; i++)
		f2nf[i] = new float[gridg];

	f3nf = new float*[gridg];							//where they move in direction 3
	for (int i = 0; i<gridg; i++)
		f3nf[i] = new float[gridg];

	f4nf = new float*[gridg];							//where they move in direction 4
	for (int i = 0; i<gridg; i++)
		f4nf[i] = new float[gridg];

	f5nf = new float*[gridg];							//where they move in direction 5
	for (int i = 0; i<gridg; i++)
		f5nf[i] = new float[gridg];


					
													//Initialization of the temporaryGrid - it counts the ants,
	f0t = new float*[gridg];							//where they move in direction 0
	for (int i = 0; i<gridg; i++)
		f0t[i] = new float[gridg];

	f1t = new float*[gridg];							//where they move in direction 1
	for (int i = 0; i<gridg; i++)
		f1t[i] = new float[gridg];

	f2t = new float*[gridg];							//where they move in direction 2
	for (int i = 0; i<gridg; i++)
		f2t[i] = new float[gridg];

	f3t = new float*[gridg];							//where they move in direction 3
	for (int i = 0; i<gridg; i++)
		f3t[i] = new float[gridg];

	f4t = new float*[gridg];							//where they move in direction 4
	for (int i = 0; i<gridg; i++)
		f4t[i] = new float[gridg];

	f5t = new float*[gridg];							//where they move in direction 5
	for (int i = 0; i<gridg; i++)
		f5t[i] = new float[gridg];

	for (int i = 0; i < gridg; i++) {
		for (int j = 0; j < gridg; j++) {
			field[i][j] = 0;

			f0nf[i][j] = 0;
			f1nf[i][j] = 0;
			f2nf[i][j] = 0;
			f3nf[i][j] = 0;
			f4nf[i][j] = 0;
			f5nf[i][j] = 0;

			f0f[i][j] = 0;
			f1f[i][j] = 0;
			f2f[i][j] = 0;
			f3f[i][j] = 0;
			f4f[i][j] = 0;
			f5f[i][j] = 0;

			f0t[i][j] = 0;
			f1t[i][j] = 0;
			f2t[i][j] = 0;
			f3t[i][j] = 0;
			f4t[i][j] = 0;
			f5t[i][j] = 0;
		}
	}

	for (int i = 0; i < gridg; i++) {
		for (int j = 0; j < 10; j++) {
			//wall below
			f0nf[gridg - 1 - j][i] = 1000;

			f3f[gridg - 1 - j][i] = 1000;

			//wall left
			f1nf[i][j] = 1000;
			f2nf[i][j] = 1000;

			f4f[i][j] = 1000;
			f5f[i][j] = 1000;

			//wall above
			f3nf[j][i] = 1000;

			f0f[j][i] = 1000;

			//wall right
			f4nf[i][gridg - 1 - j] = 1000;
			f5nf[i][gridg - 1 - j] = 1000;

			f1f[i][gridg - 1 - j] = 1000;
			f2f[i][gridg - 1 - j] = 1000;
		}
	}


	df0 = new float**[nduststep];
	df1 = new float**[nduststep];
	df2 = new float**[nduststep];
	df3 = new float**[nduststep];
	df4 = new float**[nduststep];
	df5 = new float**[nduststep];

	for (int i = 0; i < nduststep; i++) {
		df0[i] = new float*[gridg];
		df1[i] = new float*[gridg];
		df2[i] = new float*[gridg];
		df3[i] = new float*[gridg];
		df4[i] = new float*[gridg];
		df5[i] = new float*[gridg];

		for (int j = 0; j < gridg; j++) {
			df0[i][j] = new float[gridg];
			df1[i][j] = new float[gridg];
			df2[i][j] = new float[gridg];
			df3[i][j] = new float[gridg];
			df4[i][j] = new float[gridg];
			df5[i][j] = new float[gridg];
		}
	}


	for (int i = 0; i < nduststep; i++) {
		for (int j = 0; j < gridg; j++) {
			for (int k = 0; k < gridg; k++) {
				df0[i][j][k] = 0;
				df1[i][j][k] = 0;
				df2[i][j][k] = 0;
				df3[i][j][k] = 0;
				df4[i][j][k] = 0;
				df5[i][j][k] = 0;
			}
		}
	}
	cout << "initilization of Grid is Done" << endl;
}

void Grid::dust(int duststep) {
	//cout << "Im Dust: " << duststep << "  " << df0[duststep][250][250] << endl;
	for (int i = 5; i < gridg-4; i++) {
		for (int j = 5; j < gridg-4; j++) {
			f0f[i][j] -= df0[duststep][i][j];
			f0nf[i][j] -= df0[duststep][i][j];
			field[i][j] -= df0[duststep][i][j];
			df0[duststep][i][j] = 0;

			f1f[i][j] -= df1[duststep][i][j];
			f1nf[i][j] -= df1[duststep][i][j];
			field[i][j] -= df1[duststep][i][j];
			df1[duststep][i][j] = 0;

			f2f[i][j] -= df2[duststep][i][j];
			f2nf[i][j] -= df2[duststep][i][j];
			field[i][j] -= df2[duststep][i][j];
			df2[duststep][i][j] = 0;

			f3f[i][j] -= df3[duststep][i][j];
			f3nf[i][j] -= df3[duststep][i][j];
			field[i][j] -= df3[duststep][i][j];
			df3[duststep][i][j] = 0;

			f4f[i][j] -= df4[duststep][i][j];
			f4nf[i][j] -= df4[duststep][i][j];
			field[i][j] -= df4[duststep][i][j];
			df4[duststep][i][j] = 0;

			f5f[i][j] -= df5[duststep][i][j];
			f5nf[i][j] -= df5[duststep][i][j];
			field[i][j] -= df5[duststep][i][j];
			df5[duststep][i][j] = 0;
		}
	}
	this->duststep = duststep;
}

void Grid::accumulateGrids() {
	for (int i = 15; i < gridg-12; i++) {
		for (int j = 15; j < gridg-12; j++) {
			f0f[i][j] += f0t[i][j];
			f0nf[i][j] += f0t[i][j];
			field[i][j] += f0t[i][j];
			f0t[i][j] = 0;

			f1f[i][j] += f1t[i][j];
			f1nf[i][j] += f1t[i][j];
			field[i][j] += f1t[i][j];
			f1t[i][j] = 0;

			f2f[i][j] += f2t[i][j];
			f2nf[i][j] += f2t[i][j];
			field[i][j] += f2t[i][j];
			f2t[i][j] = 0;

			f3f[i][j] += f3t[i][j];
			f3nf[i][j] += f3t[i][j];
			field[i][j] += f3t[i][j];
			f3t[i][j] = 0;

			f4f[i][j] += f4t[i][j];
			f4nf[i][j] += f4t[i][j];
			field[i][j] += f4t[i][j];
			f4t[i][j] = 0;

			f5f[i][j] += f5t[i][j];
			f5nf[i][j] += f5t[i][j];
			field[i][j] += f5t[i][j];
			f5t[i][j] = 0;
		}
	}
}

void Grid::printGrid(string path) {

	ofstream ffield;
	ffield.open(path);
	for (int i = 0; i < gridg; i++) {
		for (int j = 0; j < gridg; j++) {
			ffield << field[i][j] << "\t";
		}
		ffield << endl;
	}
	ffield.close();
}
/*
struct Grid::dust {


}*/

void Grid::dGrid()
{


	for (int i = 0; i < gridg; i++) {

		delete[] f0f[i];
		delete[] f0nf[i];
		delete[] f0t[i];

		delete[] f1f[i];
		delete[] f1nf[i];
		delete[] f1t[i];

		delete[] f2f[i];
		delete[] f2nf[i];
		delete[] f2t[i];
		
		delete[] f3f[i];
		delete[] f3nf[i];
		delete[] f3t[i];
		
		delete[] f4f[i];
		delete[] f4nf[i];
		delete[] f4t[i];
		
		delete[] f5f[i];
		delete[] f5nf[i];
		delete[] f5t[i];

		delete[] field[i];
	}

	delete[] f0f;
	delete[] f0nf;
	delete[] f0t;

	delete[] f1f;
	delete[] f1nf;
	delete[] f1t;

	delete[] f2f;
	delete[] f2nf;
	delete[] f2t;

	delete[] f3f;
	delete[] f3nf;
	delete[] f3t;

	delete[] f4f;
	delete[] f4nf;
	delete[] f4t;

	delete[] f5f;
	delete[] f5nf;
	delete[] f5t;

	delete[] field;
}
