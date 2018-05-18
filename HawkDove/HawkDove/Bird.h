#ifndef _BIRD
#define _BIRD

#include <iostream>

class Bird
{
public:
	Bird(int, int);
	Bird(const Bird &);
	~Bird();
public:
	int getGenotype();
	char getAggressiveness();
	int getPoints(void);
	void fight(Bird&, int, int);
	void addPoints(int);
	void incAmountOfFights();
	int getAmountOfFights();
	int getName();

private:
	void computeAggressiveness();

private:
	int genotype;
	char aggr; //aggressiveness
	int points;
	int name;
	int amountOfFights;

public:
	static const int maxAggr;
};

#endif