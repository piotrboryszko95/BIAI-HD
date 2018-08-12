#include "Generation.h"
#include <iostream>

#define GENERATIONS 200

int main() {

	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // sluzy do wykrywania wyciekow pamieci

	std::srand(time(NULL));

	Generation * pop = new Generation(200); // drugi argument to mutationFactor <0,100>
	pop->setC(0);
	pop->setV(20);
	pop->setReplacementFactor(5);
	pop->setFightsPerGeneration(100);
	pop->setMutationChances(25);

	std::cout << std::endl;

	char ch;
	char v;
	while (true) {
		for (int i = 0; i < GENERATIONS; i++) {
			pop->live();
			std::cout << pop->getAvgAggr() << "\t" << pop->getStrongestGenotype() << std::endl;
		}
		std::cout << "Mielimy dalej?" << std::endl;
		std::cin >> ch;
		if (ch == 't') {
			std::cout << "Podaj V" << std::endl;
			std::cin >> v;
			pop->setV(v - 48);
		}
		else if (ch == 'n')
			break;
	}
	system("pause");

	delete(pop);

	return 0;
}