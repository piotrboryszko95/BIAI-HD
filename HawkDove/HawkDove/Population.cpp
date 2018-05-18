#include "Population.h"



Population::Population(int amount)
{
	populationSize = amount;
	//std::srand(time(NULL));

	birds = new Bird*[populationSize];
	for (int i = 0; i < populationSize; i++) {
		birds[i] = new Bird(rand() % INT_MAX, i);
	}

}


Population::~Population()
{
}

void Population::setV(int v)
{
	this->v = v;
}

void Population::setC(int c)
{
	this->c = c;
}

void Population::setReplacementFactor(float replacementFactor)
{
	this->replacementFactor = replacementFactor;
}


int Population::getPopulationSize()
{
	return populationSize;
}

float Population::getAvgAggr()
{
	if (birds == nullptr) {
		return -1;
	}

	long long sum = 0;
	for (int i = 0; i < populationSize; i++) {
		std::cout << i << " " << birds[i]->getGenotype() << " " << (int)birds[i]->getAggressiveness() << std::endl;
		sum += birds[i]->getAggressiveness();
	}

	avgAggr = (float)sum / (float)populationSize;
	return avgAggr;
}

void Population::fightAllBirds()
{
	int amountOfBirdsThatDidNotFightInThisRound = 0;

	preparePopulationToFight(amountOfBirdsThatDidNotFightInThisRound);

	while (amountOfBirdsThatDidNotFightInThisRound > 0) {
		fightTwoBirds(amountOfBirdsThatDidNotFightInThisRound);
	}
}

void Population::sortByFitness()
{
	// selectionsort - sortowanie przez wybor
	// Najmocniejszy osobnik po sortowaniu znajdzie sie na koncu tablicy
	// Najslabszy znajdzie sie na indeksie == 0
	Bird * tmp;
	for (int i = 0; i < populationSize; i++) {
		int minIndex = i;
		for (int j = i + 1; j < populationSize; j++) {
			if (birds[j]->getPoints() < birds[minIndex]->getPoints())
				minIndex = j;
		}

		//zamiana miejscami
		tmp = birds[minIndex];
		birds[minIndex] = birds[i];
		birds[i] = tmp;
		tmp = nullptr;
	}
	delete(tmp);
}

void Population::reproduct()
{
	int replacementIndex = (int) (replacementFactor * populationSize / 100);
	for (int i = 0; i < replacementIndex; i++) {
		birds[i] = birds[populationSize - i - 1];
	}

	int amountOfBirdsThatDidNotReproduce = 0;
	preparePopulationToReproduce(amountOfBirdsThatDidNotReproduce);
	while (amountOfBirdsThatDidNotReproduce > 0) {
		reproduceTwoBirds();
	}

}

void Population::preparePopulationToReproduce(int & amountOfBirdsThatDidNotReproduce) {
	if (populationSize % 2 == 0)
		amountOfBirdsThatDidNotReproduce = populationSize;
	else {
		amountOfBirdsThatDidNotReproduce = populationSize - 1;
		int nonReproducerIndex = rand() % populationSize;
		Bird * tmp = birds[nonReproducerIndex];
		birds[nonReproducerIndex] = birds[populationSize - 1];
		birds[populationSize - 1] = tmp;
		tmp = nullptr;
		delete(tmp);
	}
}

void Population::reproduceTwoBirds(int & amountOfBirdsThatDidNotReproduce)
{
	int brd1 = rand() % amountOfBirdsThatDidNotReproduce;
	int brd2;
	while ((brd2 = rand() % amountOfBirdsThatDidNotReproduce) == brd1);

	//birds[brd1]->fight(*birds[brd2], v, c);
	reproduce(*birds[brd1], *birds[brd2]);

	//wyrzucenie rozmnozonych ptakow na koniec tablicy
	//brd1 na amountOfBrds - 1
	Bird * tmp = birds[brd1];
	birds[brd1] = birds[amountOfBirdsThatDidNotReproduce - 1];
	birds[amountOfBirdsThatDidNotReproduce - 1] = tmp;
	//brd2 na amountOfBrds - 2
	if (brd2 == amountOfBirdsThatDidNotReproduce - 1) {
		tmp = birds[brd1];
		birds[brd1] = birds[amountOfBirdsThatDidNotReproduce - 2];
		birds[amountOfBirdsThatDidNotReproduce - 2] = tmp;
	}
	else {
		tmp = birds[brd2];
		birds[brd2] = birds[amountOfBirdsThatDidNotReproduce - 2];
		birds[amountOfBirdsThatDidNotReproduce - 2] = tmp;
	}
	tmp = nullptr;
	delete(tmp);
	amountOfBirdsThatDidNotReproduce -= 2;
}

void Population::fight(Bird & one, Bird & two)
{
	bool oneFight = false;
	bool twoFight = false;

	one.incAmountOfFights();
	two.incAmountOfFights();

	if (rand() % Bird::maxAggr <= one.getAggressiveness())
		oneFight = true;

	if (rand() % Bird::maxAggr <= two.getAggressiveness())
		twoFight = true;

	if (oneFight) {
		if (twoFight) { //oba walcza - 50% szans na wygrana + oboje ponosza koszt walki
			if (rand() % 2 == 0) {
				one.addPoints(v + c);
				two.addPoints(c);
			}
			else {
				one.addPoints(c);
				two.addPoints(v + c);
			}
		}
		else { //tylko jeden walczy, wygrywa pule, nikt nie ponosi kosztow walki
			one.addPoints(v);
		}
	}
	else {
		if (twoFight) { //tylko jeden walczy, wygrywa pule, nikt nie ponosi kosztow walki
			two.addPoints(v);
		}
		else { //nikt nie walczy, 50 % szans na wygranie puli, nikt nie ponosi kosztow walki
			if (rand() % 2 == 0) {
				one.addPoints(v);
			}
			else {
				two.addPoints(v);
			}
		}
	}
}

void Population::reproduce(Bird & one, Bird & two)
{

}

void Population::showStats()
{
	std::cout << "Index\tName\tFs\tAggr\tPts\n";
	for (int i = 0; i < populationSize; i++) {
		std::cout << i << "\t" 
			<< birds[i]->getName() << "\t"
			<< birds[i]->getAmountOfFights() << "\t"
			<< (int) birds[i]->getAggressiveness() << "\t"
			<< birds[i]->getPoints() << std::endl;
	}
	std::cout << std::endl;
}

void Population::preparePopulationToFight(int & amountOfBirdsThatDidNotFightInThisRound)
{
	if (populationSize % 2 == 0)
		amountOfBirdsThatDidNotFightInThisRound = populationSize;
	else {
		amountOfBirdsThatDidNotFightInThisRound = populationSize - 1;
		int nonFighterIndex = rand() % populationSize;
		Bird * tmp = birds[nonFighterIndex];
		birds[nonFighterIndex] = birds[populationSize - 1];
		birds[populationSize - 1] = tmp;
		tmp = nullptr;
		delete(tmp);
	}
}

void Population::fightTwoBirds(int & amountOfBirdsThatDidNotFightInThisRound)
{
	int brd1 = rand() % amountOfBirdsThatDidNotFightInThisRound;
	int brd2;
	while ((brd2 = rand() % amountOfBirdsThatDidNotFightInThisRound) == brd1);

	//birds[brd1]->fight(*birds[brd2], v, c);
	fight(*birds[brd1], *birds[brd2]);

	//wyrzucenie walczacych ptakow na koniec tablicy
	//brd1 na amountOfBrds - 1
	Bird * tmp = birds[brd1];
	birds[brd1] = birds[amountOfBirdsThatDidNotFightInThisRound - 1];
	birds[amountOfBirdsThatDidNotFightInThisRound - 1] = tmp;
	//brd2 na amountOfBrds - 2
	if (brd2 == amountOfBirdsThatDidNotFightInThisRound - 1) {
		tmp = birds[brd1];
		birds[brd1] = birds[amountOfBirdsThatDidNotFightInThisRound - 2];
		birds[amountOfBirdsThatDidNotFightInThisRound - 2] = tmp;
	}
	else {
		tmp = birds[brd2];
		birds[brd2] = birds[amountOfBirdsThatDidNotFightInThisRound - 2];
		birds[amountOfBirdsThatDidNotFightInThisRound - 2] = tmp;
	}
	tmp = nullptr;
	delete(tmp);
	amountOfBirdsThatDidNotFightInThisRound -= 2;
}
