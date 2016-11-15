#pragma once
class Ant
{
	friend class Grid;

public:
	Ant();
	Ant(Grid& grid, int reach, int nmb);
	void show();
	void dAnt();

	int x;										//X-position
	int y;										//Y-position
	int eyex;
	int eyey;
	bool eyewalk;

	int nmb;									//which ant it is
	bool food;									//Food/no Food			
	int time;									//How many time-steps since reaching Food/Nest
	int reach;									//How many foot-steps per time-step
	int step;									//wich step in reach
	int history;								//what directions took in a time-step
	float* smell = new float[6];				//which direction ant smells pheromone
	int straight0;								//Where the Ant decided to go in 0
	int straight1;								//Where the Ant decided to go in 1
	int straight2;				     			//Where the Ant decided to go in 2

	int Ant::antimanhatten();	
	int manhattenx;
	int manhatteny;
	float manhatten;

	float pheromone;

	void move(Grid& grid, float cut, float threshold, int straight);
	void eye();

	void moveStraightnf(Grid& grid, int straight);
	void findeStraight(int straight);
	void moveStraight0nf(Grid& grid);
	void moveStraight1nf(Grid& grid);
	void moveStraight2nf(Grid& grid);

	void moveStraightf(Grid& grid, int straight);
	void moveStraight0f(Grid& grid);
	void moveStraight1f(Grid& grid);
	void moveStraight2f(Grid& grid);

	void moveSmellnf(Grid& grid, float nSmell);
	void moveSmellf(Grid& grid, float nSmell);

	void moveRandomf(Grid& grid);
	void moveRandomnf(Grid& grid);


	void move0f(Grid& grid);
	void move1f(Grid& grid);
	void move2f(Grid& grid);
	void move3f(Grid& grid);
	void move4f(Grid& grid);
	void move5f(Grid& grid);

	void move0nf(Grid& grid);
	void move1nf(Grid& grid);
	void move2nf(Grid& grid);
	void move3nf(Grid& grid);
	void move4nf(Grid& grid);
	void move5nf(Grid& grid);

	void smellf(Grid& grid, float cut);
	void smellnf(Grid& grid, float cut);

	int distancef(Grid& grid);
	int distancenf(Grid& grid);

	void updatePheromomone();

	void goalwalknf(Grid& grid);
	void goalwalkf(Grid& grid);

};

