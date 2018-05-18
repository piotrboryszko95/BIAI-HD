#include "Bird.h"

const int Bird::maxAggr = 8 * sizeof(int);

Bird::Bird(int genotype, int name) {
	this->genotype = genotype;
	computeAggressiveness();
	this->name = name;
	this->points = 0;
	this->amountOfFights = 0;
}


Bird::Bird(const Bird &obj) {
	genotype = obj.genotype;
	aggr = obj.aggr;
	name = obj.name;
	points = obj.points;
	amountOfFights = obj.amountOfFights;
}


Bird::~Bird()
{
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

void Bird::fight(Bird& obj, int v, int c)
{

	bool thisFight = false;
	bool objFight = false;

	if (rand() % maxAggr <= this->getAggressiveness())
		thisFight = true;

	if (rand() % maxAggr <= obj.getAggressiveness())
		objFight = true;

	if (thisFight) {
		if (objFight) { //oba walcza - 50% szans na wygrana + oboje ponosza koszt walki
			if (rand() % 2 == 0) {
				this->addPoints(v - c);
				obj.addPoints(-c);
			}
			else {
				this->addPoints(-c);
				obj.addPoints(v - c);
			}
		}
		else { //tylko jeden walczy, wygrywa pule, nikt nie ponosi kosztow walki
			this->addPoints(v);
		}
	}
	else {
		if (objFight) { //tylko jeden walczy, wygrywa pule, nikt nie ponosi kosztow walki
			obj.addPoints(v);
		}
		else { //nikt nie walczy, 50 % szans na wygranie puli, nikt nie ponosi kosztow walki
			if (rand() % 2 == 0) {
				this->addPoints(v);
			}
			else {
				obj.addPoints(v);
			}
		}
	}
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

int Bird::getName()
{
	return name;
}


void Bird::computeAggressiveness()
{
	int bites = 8 * sizeof(int);
	aggr = 0;
	int tmpGen = genotype;

	for (int i = 0; i < bites; i++) {
		if ((tmpGen & 1) == 1) { //true, jesli na ostatnim bicie jest 1
			aggr++;
		}

		tmpGen >>= 1;
	}
}
