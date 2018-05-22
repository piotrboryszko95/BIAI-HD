#include "Generation.h"
#include <iostream>

#define GENERATIONS 5

int main() {

	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // sluzy do wykrywania wyciekow pamieci

	std::srand(time(NULL));

	//Bird ** tablica;
	//tablica = new Bird*[10];
	//for (int i = 0; i < 10; i++) {
	//	tablica[i] = new Bird(1000*i);
	//	std::cout << i << " " << tablica[i]->getGenotype() << " " << tablica[i]->getAggressiveness() << std::endl;
	//}


	Generation pop(100, 2); // drugi argument to mutationFactor <0,100>
	pop.setC(-2);
	pop.setV(1);
	pop.setReplacementFactor(10);
	pop.setFightsPerGeneration(100);

	std::cout << pop.getAvgAggr() << std::endl;
	std::cout << std::endl;


	pop.showStats();
	for (int i = 0; i < GENERATIONS; i++) {
		//pop.showStats();
		pop.live();
	}


	system("pause");

	return 0;
}