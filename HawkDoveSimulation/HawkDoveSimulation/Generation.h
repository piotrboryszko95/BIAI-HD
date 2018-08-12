#ifndef _GENERATION
#define _GENERATION

#include "Bird.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cctype>

class Generation
{
public:
	Generation(int);
	~Generation();

	void setV(int);
	void setC(int);
	void setFightsPerGeneration(int);
	void setReplacementFactor(int);
	void setMutationChances(int);

	int getPopulationSize();
	double getAvgAggr();
	int getStrongestGenotype();
	void showStats();

	void fightAllBirds();
	void live();
	void crossOverAll();
	void sortByFitness();
	void sortById();
	void select();


private:
	unsigned int genRandomInt();
	void getRandomPairOfBirds(int &, int &, int);
	int getEvenNumberOfBirds();

	void moveBirdsToTheEndOfArray(int , int , int &);
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
	int mutationFactor; //denominator; set on X means, that chances of mutation in each generation are 1/X
};

#endif