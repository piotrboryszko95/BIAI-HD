#ifndef _POPULATION
#define _POPULATION

#include "Bird.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

class Population
{
public:
	Population(int);
	~Population();

	void setV(int);
	void setC(int);
	void setReplacementFactor(float);
	int getPopulationSize();
	float getAvgAggr();
	void fightAllBirds();
	void sortByFitness();
	void reproduct();
	void showStats();

private:
	void preparePopulationToFight(int &);
	void fightTwoBirds(int &);
	void preparePopulationToReproduce(int &);
	void reproduceTwoBirds(int &);
	void fight(Bird &, Bird &);
	void reproduce(Bird &, Bird &);

private:
	Bird ** birds;
	int populationSize;
	float avgAggr;
	int v; //zysk
	int c; //strata
	float replacementFactor;
};

#endif