// Fermants.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Ant.h"
#include "Grid.h"
#include "utilities.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
using namespace std;


int main()
{

	int gridg  = 200;									//Gridsize
	int nswarm = 500;									//Swarmsize	
	int startx = 100;										//StartX of the swarm
	int starty = 50;										//StartY of the swarm
	int foodx = 100;										//FoodY
	int foody = 100;										//FoodX
	int reach = 12;										//How many Steps per Timestep
	int timeSteps = 100;									//How many Timesteps
	int straight = gridg ;							//How far the ant walkt straight
	int cut = 3;										//How likely an ant is willing to cut the corner
	int threshold = 3.0;									//At which Pheromon an ant is willing to evaluate
	
	int abgabe = 0;
	int* pabgabe = &abgabe;

	int nduststep = 20;
	int intervaldust = 3;
	int duststep = 0;


	//Random seed
	srand((unsigned)time(NULL));

	//Initialization of the GRID
	Grid grid(gridg, nduststep, startx, starty, foodx, foody);

	// Initialization of the SWARM
	Ant* ants = new Ant[nswarm];
	for (int nmb = 0; nmb < nswarm; nmb++) {
		ants[nmb] = Ant(grid, reach, nmb);
	}

	int timeindex = 0;
	ofstream animation;
	animation.open("Data//animation.txt");

	for (int i = 0; i < 50; i++) {
		animation << ants[i].x << "\t" << ants[i].y << "\t";
	}
	animation << endl;
	animation.close();


	for (int t = 1; t < timeSteps; t++) {
		cout << t << endl;
		for (int nmb = 0; nmb < nswarm; nmb++) {
			ants[nmb].move(grid, cut, threshold,straight);
		}
		if (t%intervaldust == 0) {
			cout << "Time " << t << endl;
			//grid.printGrid("Data//" + to_string(timeindex) + "Field.txt");
			timeindex += 1;
			duststep = (t / intervaldust)%nduststep;
			grid.dust(duststep);
		}
		grid.printGrid("Data//" + to_string(timeindex) + "Field.txt");
		grid.accumulateGrids();
		//grid.printGrid( "Data//" + to_string(t) + "Field.txt");
		ofstream animation;
		animation.open("Data//animation.txt", fstream::app | fstream::out);

		for (int i = 0; i < 50; i++) {
			animation << ants[i].x << "\t" << ants[i].y << "\t";
		}
		animation << endl;
		animation.close();
	}

	cout << "Hat es geschafft" << endl;
	grid.printGrid("Data//FinishedField.txt");

	grid.dGrid();

	system("pause");
    return 0;
}

