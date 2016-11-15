#include "stdafx.h"
#include "utilities.h"

void initialisazion(int gridg) {

	int** field;									//Initialization of the Grid - it counts the ants,
	field = new int*[gridg];						//where they are
	for (int i = 0; i<gridg; i++)
		field[i] = new int[gridg];

	int** f0;										//Initialization of the Grid - it counts the ants,
	f0 = new int*[gridg];							//where they move in direction 0
	for (int i = 0; i<gridg; i++)
		f0[i] = new int[gridg];

	int** f1;										//Initialization of the Grid - it counts the ants,
	f1 = new int*[gridg];							//where they move in direction 1
	for (int i = 0; i<gridg; i++)
		f1[i] = new int[gridg];

	int** f2;										//Initialization of the Grid - it counts the ants,
	f2 = new int*[gridg];							//where they move in direction 2
	for (int i = 0; i<gridg; i++)
		f2[i] = new int[gridg];

	int** f3;										//Initialization of the Grid - it counts the ants,
	f3 = new int*[gridg];							//where they move in direction 3
	for (int i = 0; i<gridg; i++)
		f3[i] = new int[gridg];

	int** f4;										//Initialization of the Grid - it counts the ants,
	f4 = new int*[gridg];							//where they move in direction 4
	for (int i = 0; i<gridg; i++)
		f4[i] = new int[gridg];

	int** f5;										//Initialization of the Grid - it counts the ants,
	f5 = new int*[gridg];							//where they move in direction 5
	for (int i = 0; i<gridg; i++)
		f5[i] = new int[gridg];

}