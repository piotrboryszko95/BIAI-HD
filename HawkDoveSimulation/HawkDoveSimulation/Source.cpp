#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <SFML\Graphics.hpp>
#include "Generation.h"
#include "Scene.h"

std::string doubleCommaSeparated(double value);

int main(int argc, char * argv[]) {


	std::srand(time(NULL));
	int V = 2;
	int C = 1;
	if (argc < 3) {
		std::cout << "Ustawiono domyslne parametry: V=2 i C=1" << std::endl;
	}
	else {
		V = atoi(argv[1]);
		C = atoi(argv[2]);
	}

	int generations = 0;
	int step = 10;
	std::fstream outputFile;
	outputFile.open("lastSimulationData.csv", std::ios::out);
	if (!outputFile.is_open()) {
		std::cout << "Nie udalo sie otworzyc pliku wyjsciowego" << std::endl;
		return -2;
	}

	if (argc > 3) {
		generations = atoi(argv[3]);

	}

	if (argc > 4) {
		step = atoi(argv[4]);
	}

	double avgAggr = 0.0f;
	int i = 0;
	Scene scene(10.0f);
	scene.setStateBarPosition(100.0f, 100.0f);
	scene.setStateBarSize(600.0f, 20.0f);
	scene.setC(C);
	scene.setV(V);
	scene.setGeneration(i);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Hawk-Dove Simulation");

	Generation * gen = new Generation(200);
	gen->setC(C);
	gen->setV(V);
	gen->setFightsPerGeneration(100);
	gen->setReplacementFactor(5);
	gen->setMutationChances(25*200);
	gen->setBitsToMutate(1);


	bool wasMouseButtonReleased = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonReleased)
				wasMouseButtonReleased = true;
		}

		if (wasMouseButtonReleased) {

			wasMouseButtonReleased = false;
			sf::Vector2f mousePos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			switch (scene.checkButtonPressed(mousePos)) {
			case Scene::upC:
				C++;
				gen->setC(C);
				scene.setC(C);
				break;
			case Scene::downC:
				C--;
				gen->setC(C);
				scene.setC(C);
				break;
			case Scene::upV:
				V++;
				gen->setV(V);
				scene.setV(V);
				break;
			case Scene::downV:
				V--;
				gen->setV(V);
				scene.setV(V);
				break;
			default:
				break;
			}
		}

		gen->live();
		avgAggr = gen->getAvgAggr();
		scene.updateStateBar(avgAggr / Bird::maxAggr);
		std::cout << avgAggr << "\t" << std::bitset<32>(gen->getStrongestGenotype()).to_string() << std::endl;

		scene.setGeneration(i);

		if (i % step == 0) {
			outputFile << i << ";" << doubleCommaSeparated(avgAggr) << std::endl;
		}

		if (i >= generations) {
			if (argc > 3)
				break;
		}

		window.clear();
		scene.draw(window);
		window.display();
		i++;
	}

	outputFile.close();

	delete(gen);

	return 0;
}

std::string doubleCommaSeparated(double value)
{
	std::string tmp = std::to_string(value);
	char * chs = (char*)tmp.c_str();
	int i = 0;
	while (chs[i] != '\0') {
		if (chs[i] == '.')
			chs[i] = ',';
		i++;
	}
	std::string ret(chs);
	return ret;
}
