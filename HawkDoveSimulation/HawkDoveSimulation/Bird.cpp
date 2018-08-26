#include "Bird.h"

const int Bird::maxAggr = 8 * sizeof(int);

Bird::Bird(int genotype, int id) {
	this->genotype = genotype;
	computeAggressiveness();
	this->id = id;
	this->points = 0;
	this->amountOfFights = 0;
}


Bird::Bird(const Bird &obj) {
	genotype = obj.genotype;
	aggr = obj.aggr;
	id = obj.id;
	points = obj.points;
	amountOfFights = obj.amountOfFights;
}


Bird::~Bird()
{
}

void Bird::setGenotype(int genotype)
{
	this->genotype = genotype;
}

int Bird::getGenotype()
{
	return genotype;
}

char Bird::getAggressiveness()
{
	return aggr;
}

int Bird::getPoints(void)
{
	return this->points;
}

void Bird::addPoints(int pts)
{
	this->points += pts;
}

void Bird::incAmountOfFights()
{
	amountOfFights++;
}

int Bird::getAmountOfFights()
{
	return amountOfFights;
}

int Bird::getId()
{
	return id;
}

bool Bird::isFighting()
{
	return (rand() % Bird::maxAggr) <= getAggressiveness();
}

void Bird::mutate()
{
	genotype ^= 7 << rand() % (sizeof(int) * CHAR_BIT - 3); // zamien trzy bity losowo wybrane
}

double Bird::mutateDouble() {
	int bit = 1;
	bit = bit << rand() % 32;
	genotype ^= bit;
	return genotype;
}

void Bird::renew()
{
	points = 0;
	amountOfFights = 0;
	computeAggressiveness();
}

void Bird::computeAggressiveness()
{
	int bits = 8 * sizeof(int);
	aggr = 0;
	int tmpGen = genotype;

	for (int i = 0; i < bits; i++) {
		if ((tmpGen & 1) == 1) { //true, jesli na ostatnim bicie jest 1
			aggr++;
		}

		tmpGen >>= 1;
	}
}
