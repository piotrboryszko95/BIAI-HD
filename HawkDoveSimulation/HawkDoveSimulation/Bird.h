#ifndef _BIRD
#define _BIRD

#include <iostream>
#include <cctype>

class Bird
{
public:
	Bird(int, int);
	Bird(const Bird &);
	~Bird();

	void setGenotype(int);

	int getGenotype();
	char getAggressiveness();
	int getPoints(void);
	int getAmountOfFights();
	int getId();

	void addPoints(int);
	void incAmountOfFights();
	bool isFighting();
	double mutate(int);
	void renew();

private:
	void computeAggressiveness();

private:
	int genotype;
	int aggr; //aggressiveness
	int points; // fitness points
	int id;
	int amountOfFights;

public:
	static const int maxAggr;
};

#endif