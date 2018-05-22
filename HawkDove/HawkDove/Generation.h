#ifndef _GENERATION
#define _GENERATION

#include "Bird.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

class Generation
{
public:
	Generation(int, int);
	~Generation();

	void setV(int);
	void setC(int);
	void setFightsPerGeneration(int);
	void setReplacementFactor(int);
	int getPopulationSize();
	double getAvgAggr();
	void fightAllBirds();
	void live();
	void crossOverAll();
	void sortByFitness();
	void sortById();
	void showStats();
	void select();


private:
	unsigned int genRandomInt();
	void getRandomPairOfBirds(int &, int &, int);
	void moveBirdsToTheEndOfArray(int , int , int &);
	int getEvenNumberOfBirds();
	void fight(Bird &, Bird &);
	void crossOver(Bird &, Bird &);

private:
	Bird ** birds;
	int populationSize;
	double avgAggr;
	int v; //zysk
	int c; //strata
	int replacementFactor;
	int fightsPerGeneration;
};

#endif