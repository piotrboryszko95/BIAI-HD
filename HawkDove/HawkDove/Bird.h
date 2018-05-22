#ifndef _BIRD
#define _BIRD

#include <iostream>

class Bird
{
public:
	Bird(int, int, int);
	Bird(const Bird &);
	~Bird();
public:
	void setGenotype(int);
	int getGenotype();
	char getAggressiveness();
	int getPoints(void);
	void fight(Bird&, int, int);
	void addPoints(int);
	void incAmountOfFights();
	int getAmountOfFights();
	int getId();
	bool isFighting();
	void mutate();
	void renew();

private:
	void computeAggressiveness();

private:
	int genotype;
	int aggr; //aggressiveness
	int points; // fitness points
	int id;
	int amountOfFights;
	int mutationFactor;

public:
	static const int maxAggr;
};

#endif