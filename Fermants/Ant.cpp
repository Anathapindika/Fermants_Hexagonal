#include "stdafx.h"
#include "Ant.h"
#include "Grid.h"
#include <iostream>
#include <numeric>
#include <math.h>

using namespace std;

Ant::Ant() {

}

Ant::Ant(Grid& grid, int reach, int nmb)
{
	
	this->x = grid.startx;
	this->y = grid.starty;
	this->reach = reach;
	step = 0;
	this->nmb = nmb;
	time = 0;
	pheromone = 2;
	food = false;
	straight0 = 0;
	straight1 = 0;
	straight2 = 0;

	eyex = 0;
	eyey = 0;
	eyewalk = true;

	manhattenx = grid.startx;
	manhatteny = grid.starty;


	for (int i = 0; i < 6; i++) {
		smell[i] = 0.0;
	}
	history = 10;
}

void Ant::updatePheromomone() {
	if (food) { pheromone = 2 - time / 50.0;}
	else { pheromone = 1 - time / 50.0; }
	if (pheromone < 0) { pheromone = 0; }
}

void Ant::dAnt()
{
	delete[] smell;
}

void Ant::move0nf(Grid& grid) {

	grid.f0t[y][x] += pheromone;
	grid.df0[grid.duststep][y][x] += pheromone;
	y -= 1;
	history = 0;
}

void Ant::move1nf(Grid& grid) {

	grid.f1t[y][x] += pheromone;
	grid.df1[grid.duststep][y][x] += pheromone;
	y -= x % 2;
	x += 1;
	history = 1;
}

void Ant::move2nf(Grid& grid) {

	if (history == 5) {
		moveRandomnf(grid);
		return;
	}
	grid.f2t[y][x] += pheromone;
	grid.df2[grid.duststep][y][x] += pheromone;
	y += 1 - x % 2;
	x += 1;
	history = 2;
}

void Ant::move3nf(Grid& grid) {

	grid.f3t[y][x] += pheromone;
	grid.df3[grid.duststep][y][x] += pheromone;
	y += 1;
	history = 3;
}

void Ant::move4nf(Grid& grid) {

	grid.f4t[y][x] += pheromone;
	grid.df4[grid.duststep][y][x] += pheromone;
	y += 1 - x % 2;
	x -= 1;
	history = 4;
}

void Ant::move5nf(Grid& grid) {

	grid.f5t[y][x] += pheromone;
	grid.df5[grid.duststep][y][x] += pheromone;
	y -= x % 2;
	x -= 1;
	history = 5;
}

void Ant::move0f(Grid& grid) {

	y -= 1;
	grid.f3t[y][x] += pheromone;
	grid.df3[grid.duststep][y][x] += pheromone;
	history = 0;
}

void Ant::move1f(Grid& grid) {

	y -= x % 2;
	x += 1;
	grid.f4t[y][x] += pheromone;
	grid.df4[grid.duststep][y][x] += pheromone;
	history = 1;
}

void Ant::move2f(Grid& grid) {

	y += 1 - x % 2;
	x += 1;
	grid.f5t[y][x] += pheromone;
	grid.df5[grid.duststep][y][x] += pheromone;
	history = 2;
}

void Ant::move3f(Grid& grid) {

	y += 1;
	grid.f0t[y][x] += pheromone;
	grid.df0[grid.duststep][y][x] += pheromone;
	history = 3;
}

void Ant::move4f(Grid& grid) {

	y += 1 - x % 2;
	x -= 1;
	grid.f1t[y][x] += pheromone;
	grid.df1[grid.duststep][y][x] += pheromone;
	history = 4;
}

void Ant::move5f(Grid& grid) {

	y -= x % 2;
	x -= 1;
	grid.f2t[y][x] += pheromone;
	grid.df2[grid.duststep][y][x] += pheromone;
	history = 5;
}

void Ant::smellnf(Grid& grid, float cut) {
	int chi = x % 2;
	smell[0] = cut*grid.f0nf[y][x];
	//smell[0] += grid.f0nf[y - 1][x];
	//smell[0] += grid.f0nf[y - chi][x + 1];
	//smell[0] += grid.f0nf[y - chi][x - 1];

	smell[1] = cut*grid.f1nf[y][x];
	//smell[1] += grid.f1nf[y - chi][x + 1];
	//smell[1] += grid.f1nf[y + 1 - chi][x + 1];
	//smell[1] += grid.f1nf[y - 1][x];

	smell[2] = cut*grid.f2nf[y][x];
	//smell[2] += grid.f2nf[y + 1 - chi][x + 1];
	//smell[2] += grid.f2nf[y + 1][x];
	//smell[2] += grid.f2nf[y - chi][x + 1];

	smell[3] = cut*grid.f3nf[y][x];
	//smell[3] += grid.f3nf[y + 1][x];
	//smell[3] += grid.f3nf[y + 1 - chi][x - 1];
	//smell[3] += grid.f3nf[y + 1 - chi][x + 1];

	smell[4] = cut*grid.f4nf[y][x];
	//smell[4] += grid.f4nf[y + 1 - chi][x - 1];
	//smell[4] += grid.f4nf[y - chi][x - 1];
	//smell[4] += grid.f4nf[y + 1][x];

	smell[5] = cut*grid.f5nf[y][x];
	//smell[5] += grid.f5nf[y - chi][x - 1];
	//smell[5] += grid.f5nf[y - 1][x];
	//smell[5] += grid.f5nf[y + 1 - chi][x - 1];
}

void Ant::smellf(Grid& grid, float cut) {
	int chi = x % 2;

	smell[0]  = cut*grid.f3f[y-1][x];
	//smell[0] += grid.f3f[y - 2][x];
	//smell[0] += grid.f3f[y - 1 - chi][x + 1];
	//smell[0] += grid.f3f[y - 1 - chi][x - 1];

	smell[1] = cut*grid.f4f[y - chi][x + 1];
	//smell[1] += grid.f4f[y - 1][x + 2];
	//smell[1] += grid.f4f[y][x + 2];
	//smell[1] += grid.f4f[y - 1 - chi][x + 1];

	smell[2] = cut*grid.f5f[y + 1 - chi][x+1];
	//smell[2] += grid.f5f[y + 1][x + 2];
	//smell[2] += grid.f5f[y][x + 2];
	//smell[2] += grid.f5f[y + 2 - chi][x + 1];

	smell[3] = cut*grid.f0f[y+1][x];
	//smell[3] += grid.f0f[y + 2][x];
	//smell[3] += grid.f0f[y + 2 - chi][x - 1];
	//smell[3] += grid.f0f[y + 2 - chi][x + 1];

	smell[4] = cut*grid.f1f[y + 1 - chi][x-1];
	//smell[4] += grid.f1f[y + 1][x - 2];
	//smell[4] += grid.f1f[y + 2 - chi][x - 1];  
	//smell[4] += grid.f1f[y][x - 2];

	smell[5] = cut*grid.f2f[y - chi][x - 1];
	//smell[5] += grid.f2f[y - 1][x - 2];
	//smell[5] += grid.f2f[y - 1 - chi][x - 1];
	//smell[5] += grid.f2f[y][x - 2];
}

void Ant::show() {
	cout << "Ant nmb:"<<nmb<<"\tcomponent:" << x << "\tY-component:" << y << "\t" << "Food:" << food << endl;
}

void Ant::moveRandomf(Grid& grid) {


	int rnd = rand() % 6;

	if (rnd == history + 3 % 5) {
		rnd += rand() % 5;
		rnd = rnd % 5;
	}

	if (rnd == 0) {
		move0f(grid);
	}
	else if (rnd == 1) {
		move1f(grid);
	}
	else if (rnd == 2) {
		move2f(grid);
	}
	else if (rnd == 3) {
		move3f(grid);
	}
	else if (rnd == 4) {
		move4f(grid);
	}
	else {
		move5f(grid);
	}
}

void Ant::moveRandomnf(Grid& grid) {

	int rnd = rand() % 6;

	if (rnd == history + 3 % 5) {
		rnd += rand() % 5;
		rnd = rnd % 5;
	}

	if (rnd == 0) {
		move0nf(grid);
	}
	else if (rnd == 1) {
		move1nf(grid);
	}
	else if (rnd == 2) {
		move2nf(grid);
	}
	else if (rnd == 3) {
		move3nf(grid);
	}
	else if (rnd == 4) {
		move4nf(grid);
	}
	else {
		move5nf(grid);
	}
}

void Ant::moveStraightnf(Grid& grid, int straight) {
	int nSmell = accumulate(smell, smell + 6, 0);
	//nsmell = smell[0] + smell[1] + smell[2] + smell[3] + smell[4] + smell[5];
	
	if (!straight0 && !straight1 && !straight2) {
		findeStraight(straight);
		//cout << "Now   NMB:" << nmb << "   straights: " << straight0 << "  " << straight1 << "  " << straight2 << endl;
	}

	int rnd0 = 0;
	int rnd1 = 0;
	int rnd2 = 0;

	if (straight0) {
		rnd0 = rand() % abs(straight0);
	}
	if (straight1) {
		rnd1 = rand() % abs(straight1);
	}
	if (straight2) {
		rnd2 = rand() % abs(straight2);
	}
	
	int max = 1;

	if (rnd0 > rnd1 && rnd0 > rnd2) {
		moveStraight0nf(grid);
	}
	else if (rnd1 > rnd0 && rnd1 > rnd2) {
		moveStraight1nf(grid);
	}
	else if (rnd2 > rnd0 && rnd2 > rnd1) {
		moveStraight2nf(grid);
	}
	else {
		if (abs(straight0) > abs(straight1) && abs(straight0) > abs(straight2)) {
			moveStraight0nf(grid);
		}
		else if (abs(straight1) > abs(straight2) && abs(straight1) > abs(straight0)) {
			moveStraight1nf(grid);
		}
		else if (abs(straight2) > abs(straight1) && abs(straight2) > abs(straight0)) {
			moveStraight2nf(grid);
		}

		else {
			int whichway = rand() % 2;
			if (!straight0) {
				if (whichway == 0) {
					moveStraight1nf(grid);
				}
				else {
					moveStraight2nf(grid);
				}
			}
			else if (!straight1) {
				if (whichway == 0) {
					moveStraight0nf(grid);
				}
				else {
					moveStraight2nf(grid);
				}
			}
			else {
				if (whichway == 0) {
					moveStraight0nf(grid);
				}
				else {
					moveStraight1nf(grid);
				}
			}
		}
	}
}


void Ant::moveStraight0nf(Grid& grid) {
	if (straight0 > 0) {
		move0nf(grid);
		straight0 -= 1;
	}

	else {
		move3nf(grid);
		straight0 += 1;
	}
}

void Ant::moveStraight1nf(Grid& grid) {
	if (straight1 > 0) {
		move1nf(grid);
		straight1 -= 1;
	}

	else {
		move4nf(grid);
		straight1 += 1;
	}
}

void Ant::moveStraight2nf(Grid& grid) {
	if (straight2 > 0) {
		move2nf(grid);
		straight2 -= 1;
	}

	else {
		move5nf(grid);
		straight2 += 1;
	}
}

void Ant::moveStraightf(Grid& grid, int straight) {
	int nSmell = accumulate(smell, smell + 6, 0);

	if (!straight0 && !straight1 && !straight2) {
		findeStraight(straight);
	}

	int rnd0 = 0;
	int rnd1 = 0;
	int rnd2 = 0;

	if (straight0) {
		rnd0 = rand() % abs(straight0);
	}
	if (straight1) {
		rnd1 = rand() % abs(straight1);
	}
	if (straight2) {
		rnd2 = rand() % abs(straight2);
	}

	int max = 1;

	if (rnd0 > rnd1 && rnd0 > rnd2) {
		moveStraight0f(grid);
	}
	else if (rnd1 > rnd0 && rnd1 > rnd2) {
		moveStraight1f(grid);
	}
	else if (rnd2 > rnd0 && rnd2 > rnd1) {
		moveStraight2f(grid);
	}
	else {
		if (abs(straight0) > abs(straight1) && abs(straight0) > abs(straight2)) {
			moveStraight0f(grid);
		}
		else if (abs(straight1) > abs(straight2) && abs(straight1) > abs(straight0)) {
			moveStraight1f(grid);
		}
		else if (abs(straight2) > abs(straight1) && abs(straight2) > abs(straight0)) {
			moveStraight2f(grid);
		}

		else {
			int whichway = rand() % 2;
			if (!straight0) {
				if (whichway == 0) {
					moveStraight1f(grid);
				}
				else {
					moveStraight2f(grid);
				}
			}
			else if (!straight1) {
				if (whichway == 0) {
					moveStraight0f(grid);
				}
				else {
					moveStraight2f(grid);
				}
			}
			else {
				if (whichway == 0) {
					moveStraight0f(grid);
				}
				else {
					moveStraight1f(grid);
				}
			}
		}
	}
}


void Ant::moveStraight0f(Grid& grid) {
	if (straight0 > 0) {
		move0f(grid);
		straight0 -= 1;
	}

	else {
		move3f(grid);
		straight0 += 1;
	}
}

void Ant::moveStraight1f(Grid& grid) {
	if (straight1 > 0) {
		move1f(grid);
		straight1 -= 1;
	}

	else {
		move4f(grid);
		straight1 += 1;
	}
}

void Ant::moveStraight2f(Grid& grid) {
	if (straight2 > 0) {
		move2f(grid);
		straight2 -= 1;
	}

	else {
		move5f(grid);
		straight2 += 1;
	}
}

void Ant::findeStraight(int straight) {
	int rnd;
	int rnd2;
	straight = rand() % straight + 2;
	rnd = rand() % 3;
	if (rnd == 0) {
		straight0 = 0;
		straight1 = rand() % straight;
		straight2 = straight - straight1;

		rnd2 = rand() % 2;
		if(rnd2){
			straight1 = -straight1;
			straight2 = -straight2;
		}
	}
	else if (rnd == 1) {
		straight0 = rand() % straight;
		straight1 = 0;
		straight2 = straight - straight0;
		rnd2 = rand() % 2;
		if (rnd2) {
			straight0 = -straight0;
		}
		else {
			straight2 = -straight2;
		}
	}
	else {
		straight0 = rand() % straight;
		straight1 = straight - straight0;
		straight2 = 0;
		rnd2 = rand() % 2;
		if (rnd2) {
			straight0 = -straight0;
			straight1 = -straight1;
		}
	}
}

void Ant::moveSmellnf(Grid& grid, float nSmell) {

	float prob0 = smell[0] / nSmell;
	float prob1 = prob0 + smell[1] / nSmell;
	float prob2 = prob1 + smell[2] / nSmell;
	float prob3 = prob2 + smell[3] / nSmell;
	float prob4 = prob3 + smell[4] / nSmell;
	float prob5 = prob4 + smell[5] / nSmell;
	//cout << endl << endl << "Auswertung OHNE FOOD" << endl;
	//cout << smell[0] << "\t" << smell[1] << "\t" << smell[2] << "\t" << smell[3] << "\t" << smell[4] << "\t" << smell[5] << "\t\t" << nSmell << endl;
	//cout << prob0 << "\t" << prob1 << "\t" << prob2 << "\t" << prob3 << "\t" << prob4 << "\t" << prob5 << endl;

	float rnd = rand() / (float)(RAND_MAX);

	straight0 = straight1 = straight2 = 0;

	if (rnd < prob0) {
		move0nf(grid);
		//cout << "Go 0  " << nmb << "   " << x << "   " << y << endl;
	}
	else if (rnd < prob1) {
		move1nf(grid);
		//cout << "Go 1  " << nmb << "   " << x << "   " << y << endl;
	}
	else if (rnd < prob2) {
		move2nf(grid);
		//cout << "Go 2  " << nmb << "   " << x << "   " << y << endl;
	}
	else if (rnd < prob3) {
		move3nf(grid);
		//cout << "Go 3  " << nmb << "   " << x << "   " << y << endl;
	}
	else if (rnd < prob4) {
		move4nf(grid);
		//cout << "Go 4  " << nmb << "   " << x << "   " << y << endl;
	}
	else{
		move5nf(grid);
		//cout << "Go 5  " << nmb << "   " << x << "   " << y << endl;
	}
}

void Ant::moveSmellf(Grid& grid, float nSmell) {

	float prob0 = smell[0] / nSmell;
	float prob1 = prob0 + smell[1] / nSmell;
	float prob2 = prob1 + smell[2] / nSmell;
	float prob3 = prob2 + smell[3] / nSmell;
	float prob4 = prob3 + smell[4] / nSmell;
	float prob5 = prob4 + smell[5] / nSmell;
	//cout << endl << endl << "Auswertung mit FOOD" << endl;
	//cout << smell[0] << "\t" << smell[1] << "\t" << smell[2] << "\t" << smell[3] << "\t" << smell[4] << "\t" << smell[5] << "\t\t" << nSmell << endl;
	//cout << prob0 << "\t" << prob1 << "\t" << prob2 << "\t" << prob3 << "\t" << prob4 << "\t" << prob5 << endl;

	float rnd = rand() / (float)(RAND_MAX);

	straight0 = straight1 = straight2 = 0;

	if (rnd < prob0) {
		move0f(grid);
		//cout << "Go 0  " << nmb << "   " << x << "   " << y << endl;
	}
	else if (rnd < prob1) {
		move1f(grid);
		//cout << "Go 1  " << nmb << "   " << x << "   " << y << endl;
	}
	else if (rnd < prob2) {
		move2f(grid);
		//cout << "Go 2  " << nmb << "   " << x << "   " << y << endl;
	}
	else if (rnd < prob3) {
		move3f(grid);
		//cout << "Go 3  " << nmb << "   " << x << "   " << y << endl;
	}
	else if (rnd < prob4) {
		move4f(grid);
		//cout << "Go 4  " << nmb << "   " << x << "   " << y << endl;
	}
	else {
		move5f(grid);
		//cout << "Go 5  " << nmb << "   " << x << "   " << y << endl;
	}
}
int Ant::antimanhatten() {

	int dx;
	int dy;
	dx = abs(x - manhattenx);
	dy = abs(y - manhatteny);
	

	manhatten = reach - sqrt(dx*dx + dy*dy);
	int gain = manhatten;
	manhatten -= gain;
	return gain;

}

void Ant::move(Grid& grid, float cut, float threshold, int straight) {
	float nSmell;
	int distance;
	updatePheromomone();
	eye();
	eyex = x;
	eyey = y;
	int gain = antimanhatten();
	gain = 0;
	manhattenx = x;
	manhatteny = y;
	if (food) {
		threshold /= 4;
		distance = distancef(grid);
		if (distance>40) {
			for (int i = 0; i < reach + gain; i++) {
				smellf(grid, cut);
				nSmell = accumulate(smell, smell + 6, 0);
				nSmell = smell[0] + smell[1] + smell[2] + smell[3] + smell[4] + smell[5];

				if (nSmell >= threshold && eyewalk) {
					moveSmellf(grid, nSmell);
				}
				else {
					moveStraightf(grid, straight);
				}
			}
		}
		else {
			for (int i = 0; i < reach + gain; i++) {
				smellf(grid, cut);
				nSmell = accumulate(smell, smell + 6, 0);
				nSmell = smell[0] + smell[1] + smell[2] + smell[3] + smell[4] + smell[5];

				if (nSmell >= threshold && eyewalk) {
					moveSmellf(grid, nSmell);
				}
				else {
					moveStraightf(grid, straight);
				}
				distance = distancef(grid);
				if (distance < 15) {
					goalwalkf(grid);
					cout << "Found Start!  " << pheromone << endl;
					manhattenx = x;
					manhatteny = y;
					return;
				}
			}
		}
	}
	else {
		distance = distancenf(grid);
		if (distance > 40) {
			for (int i = 0; i < reach + gain; i++) {
				smellnf(grid, cut);
				nSmell = accumulate(smell, smell + 6, 0);
				nSmell = smell[0] + smell[1] + smell[2] + smell[3] + smell[4] + smell[5];

				if (nSmell >= threshold && eyewalk) {
					moveSmellnf(grid, nSmell);
				}
				else {
					moveStraightnf(grid, straight);
				}
			}
		}
		else{

			for (int i = 0; i < reach + gain; i++) {
				smellnf(grid, cut);
				nSmell = accumulate(smell, smell + 6, 0);
				nSmell = smell[0] + smell[1] + smell[2] + smell[3] + smell[4] + smell[5];

				if (nSmell >= threshold) {
					moveSmellnf(grid, nSmell && eyewalk);
				}
				else {
					moveStraightnf(grid, straight);
				}
				distance = distancenf(grid);
				if (distance < 15) {
					goalwalknf(grid);
					manhattenx = x;
					manhatteny = y;
					return;
				}
			}
		}
	}
	time += 1;
	step = 0;
}

int Ant::distancenf(Grid& grid) {
	int xx = abs(x - grid.foodx);
	int yy = abs(y - grid.foody);
	return xx + yy;
}

int Ant::distancef(Grid& grid) {
	int xx = abs(x - grid.startx);
	int yy = abs(y - grid.starty);
	return xx + yy;
}

void Ant::eye(){
	int xx = abs(x - eyex);
	int yy = abs(y - eyey);
	if (xx + yy < 3) {
		eyewalk = false;
	}
	else {
		eyewalk = true;
	}
}

void Ant::goalwalknf(Grid& grid) {
	int dx = x - grid.foodx;
	int dy = y - grid.foody;
	cout << "Food " << pheromone << endl;

	while (dx || dy) {
		if (abs(dx) >= abs(dy)) {
			if (dx > 0) {
				if (dy > 0) {
					move5nf(grid);
				}
				else if (dy < 0) {
					move4nf(grid);
				}
				else {
					if (!x % 2) {
						move5nf(grid);
					}
					else {
						move4nf(grid);
					}
				}
			}
			else {
				if (dy > 0) {
					move1nf(grid);
				}
				else if (dy < 0) {
					move2nf(grid);
				}
				else {
					if (!x % 2) {
						move1nf(grid);
					}
					else {
						move2nf(grid);
					}
				}
			}
		}
		else if (abs(dx) < abs(dy)) {
			if (dy > 0) {
				if (dx > 0) {
					move5nf(grid);
				}
				else if (dx < 0) {
					move1nf(grid);
				}
				else {
					move0nf(grid);
				}
			}
			else {
				if (dx > 0) {
					move4nf(grid);

				}
				else if (dx < 0) {
					move2nf(grid);
				}
				else {
					move3nf(grid);
				}
			}
		}
		dx = x - grid.foodx;
		dy = y - grid.foody;
	}
	food = true;
	time = 0;
	history = 10;
}

void Ant::goalwalkf(Grid& grid) {
	int dx = x - grid.startx;
	int dy = y - grid.starty;

	while (dx || dy) {

		if (abs(dx) >= abs(dy)) {
			if (dx > 0) {
				if (dy > 0) {
					move5f(grid);
				}
				else if (dy < 0) {
					move4f(grid);
				}
				else {
					if (!x % 2) {
						move5f(grid);
					}
					else {
						move4f(grid);
					}
				}
			}
			else {
				if (dy > 0) {
					move1f(grid);
				}
				else if (dy < 0) {
					move2f(grid);
				}
				else {
					if (!x % 2) {
						move1f(grid);
					}
					else {
						move2f(grid);
					}
				}
			}
		}
		else if (abs(dx) < abs(dy)) {
			if (dy > 0) {
				if (dx > 0) {
					move5f(grid);
				}
				else if (dx < 0) {
					move1f(grid);
				}
				else {
					move0f(grid);
				}
			}
			else {
				if (dx > 0) {
					move4f(grid);

				}
				else if (dx < 0) {
					move2f(grid);
				}
				else {
					move3f(grid);
				}
			}
		}
		dx = x - grid.startx;
		dy = y - grid.starty;
	}
	food = false;
	time = 0;
	history = 10;
}