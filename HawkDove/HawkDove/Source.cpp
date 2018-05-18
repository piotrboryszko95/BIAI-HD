#include "Population.h"
#include <iostream>

int main() {

	//Bird ** tablica;
	//tablica = new Bird*[10];
	//for (int i = 0; i < 10; i++) {
	//	tablica[i] = new Bird(1000*i);
	//	std::cout << i << " " << tablica[i]->getGenotype() << " " << tablica[i]->getAggressiveness() << std::endl;
	//}

	std::srand(time(NULL));

	Population pop(20);
	pop.setC(-2);
	pop.setV(1);
	pop.setReplacementFactor(10.0f);
	std::cout << pop.getAvgAggr() << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < 100; i++) {
		pop.fightAllBirds();
		//pop.showStats();
		//std::cout << std::endl;
		//system("pause");
	}
	pop.showStats();
	pop.sortByFitness();
	pop.showStats();
	pop.reproduct();
	pop.showStats();
	system("pause");

	return 0;
}