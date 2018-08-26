#include "Generation.h"



Generation::Generation(int populationSize)
{
	this->populationSize = populationSize;
	//std::srand(time(NULL));

	birds = new Bird*[populationSize];
	for (int i = 0; i < populationSize; i++) {
		birds[i] = new Bird(genRandomInt(), i);
	}

}


Generation::~Generation()
{
	for (int i = 0; i < populationSize; i++) {
		delete birds[i];
	}
	delete birds;
}

void Generation::setV(int v)
{
	this->v = v;
}

void Generation::setC(int c)
{
	this->c = c;
}

void Generation::setFightsPerGeneration(int fightsPerGeneration)
{
	this->fightsPerGeneration = fightsPerGeneration;
}

void Generation::setReplacementFactor(int replacementFactor)
{
	this->replacementFactor = replacementFactor;
}

void Generation::setMutationChances(int mutationFactor)
{
	this->mutationFactor = mutationFactor;
}


int Generation::getPopulationSize()
{
	return populationSize;
}

double Generation::getAvgAggr()
{
	if (birds == nullptr) {
		return -1;
	}

	long long sum = 0;
	for (int i = 0; i < populationSize; i++) {
		//std::cout << i << " " << birds[i]->getGenotype() << " " << (int)birds[i]->getAggressiveness() << std::endl;
		sum += birds[i]->getAggressiveness();
	}

	avgAggr = (double)sum / (double)populationSize;
	return avgAggr;
}

int Generation::getStrongestGenotype()
{
	return birds[populationSize - 1]->getGenotype();
}

void Generation::fightAllBirds()
{
	int remainingBirdsToFight = getEvenNumberOfBirds();	

	int bird1, bird2;
	while (remainingBirdsToFight > 0) {
		getRandomPairOfBirds(bird1, bird2, remainingBirdsToFight);
		fight(*birds[bird1], *birds[bird2]);
		moveBirdsToTheEndOfArray(bird1, bird2, remainingBirdsToFight);
	}
}

void Generation::live()
{
	
	//sortById();

	for (int i = 0; i < fightsPerGeneration; i++) {
		fightAllBirds();
	}
	//sortById();
	//showStats();
	sortByFitness();
	//showStats();
	select();
	crossOverAll();
	if (rand() % mutationFactor == 0) {
		int i = rand() % populationSize;
		birds[i]->setGenotype(birds[i]->mutateDouble());
	}
	for (int i = 0; i < populationSize; i++) {
		//birds[i]->mutate();
		birds[i]->renew();
	}
}

void Generation::sortByFitness()
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
	}
}

void Generation::sortById()  // do testow
{
	// selectionsort - sortowanie przez wybor
	// Najmocniejszy osobnik po sortowaniu znajdzie sie na koncu tablicy
	// Najslabszy znajdzie sie na indeksie == 0
	Bird * tmp;
	for (int i = 0; i < populationSize; i++) {
		int minIndex = i;
		for (int j = i + 1; j < populationSize; j++) {
			if (birds[j]->getId() < birds[minIndex]->getId())
				minIndex = j;
		}

		//zamiana miejscami
		tmp = birds[minIndex];
		birds[minIndex] = birds[i];
		birds[i] = tmp;
	}
}

void Generation::select()
{
	int replacementIndex = (int) (replacementFactor * populationSize / 100);
	for (int i = 0; i < replacementIndex; i++) {
		birds[i]->setGenotype(birds[populationSize - i - 1]->getGenotype());
		//birds[i] = birds[/*rand() % */(populationSize - replacementIndex) + replacementIndex];
	}
}

void Generation::crossOverAll()
{
	int remainingBirdsToCrossOver = getEvenNumberOfBirds();

	int bird1, bird2;
	while (remainingBirdsToCrossOver > 0) {
		getRandomPairOfBirds(bird1, bird2, remainingBirdsToCrossOver);
		crossOver(*birds[bird1], *birds[bird2]);
		moveBirdsToTheEndOfArray(bird1, bird2, remainingBirdsToCrossOver);
	}
}

int Generation::getEvenNumberOfBirds() {
	if (populationSize % 2 == 0)
		return populationSize;
	else {
		int leftAloneBirdIndex = rand() % populationSize;
		Bird * tmp = birds[leftAloneBirdIndex];
		birds[leftAloneBirdIndex] = birds[populationSize - 1];
		birds[populationSize - 1] = tmp;
		return populationSize - 1;
	}
}

void Generation::fight(Bird & one, Bird & two)
{
	one.incAmountOfFights();
	two.incAmountOfFights();

	if (one.isFighting()) {
		if (two.isFighting()) { //oba walcza - 50% szans na wygrana + oboje ponosza koszt walki
			if (rand() % 2 == 0) {
				one.addPoints(v - c);
				two.addPoints(-c);
			}
			else {
				one.addPoints(-c);
				two.addPoints(v - c);
			}
		}
		else { //tylko jeden walczy, wygrywa pule, nikt nie ponosi kosztow walki
			one.addPoints(v);
		}
	}
	else {
		if (two.isFighting()) { //tylko jeden walczy, wygrywa pule, nikt nie ponosi kosztow walki
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

void Generation::showStats()
{
	std::cout << "Index\tId\tFs\tAggr\tPts\n";
	for (int i = 0; i < populationSize; i++) {
		std::cout << i << "\t" 
			<< birds[i]->getId() << "\t"
			<< birds[i]->getAmountOfFights() << "\t"
			<< (int) birds[i]->getAggressiveness() << "\t"
			<< birds[i]->getPoints() << std::endl;
	}
	std::cout << std::endl;
}

void Generation::crossOver(Bird &bird1, Bird &bird2)
{
	unsigned int tmp1 = bird1.getGenotype();
	unsigned int tmp2 = bird1.getGenotype();
	unsigned int tmp3 = bird2.getGenotype();
	unsigned int tmp4 = bird2.getGenotype();
	//int lol = sizeof(int);
	tmp1 &= 0xffff0000;
	tmp2 &= 0x0000ffff;
	tmp3 &= 0xffff0000;
	tmp4 &= 0x0000ffff;
	tmp1 |= tmp4;
	tmp2 |= tmp3;
	bird1.setGenotype(tmp1);
	bird2.setGenotype(tmp2);
}

unsigned int Generation::genRandomInt() { // dalej ma³y rozrzut wartosci
	const int BITS_PER_RAND = (int)(log2(RAND_MAX / 2 + 1) + 1.0); /* Or log(RAND_MAX + 1) / log(2) with older language standards */
	unsigned int ret = 0;
	for (int i = 0; i < sizeof(int) * CHAR_BIT; i += BITS_PER_RAND) {
		ret <<= BITS_PER_RAND;
		ret |= rand();
	}
	return ret;
}

void Generation::getRandomPairOfBirds(int &bird1, int &bird2, int population)
{
	bird1 = rand() % population;

	bird2;
	while ((bird2 = rand() % population) == bird1)
		;
}

void Generation::moveBirdsToTheEndOfArray(int bird1, int bird2, int & population)
{
	//brd1 na amountOfBrds - 1
	Bird * tmp = birds[bird1];
	birds[bird1] = birds[population - 1];
	birds[population - 1] = tmp;

	//brd2 na amountOfBrds - 2
	if (bird2 == population - 1) {
		tmp = birds[bird1];
		birds[bird1] = birds[population - 2];
		birds[population - 2] = tmp;
	}
	else {
		tmp = birds[bird2];
		birds[bird2] = birds[population - 2];
		birds[population - 2] = tmp;
	}
	population -= 2;
}
