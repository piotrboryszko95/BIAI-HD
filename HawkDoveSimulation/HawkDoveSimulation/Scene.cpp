#include "Scene.h"



Scene::Scene(float buttonRadius)
{
	this->buttonRadius = buttonRadius;

	if (!font.loadFromFile("OpenSans-Regular.ttf")) {
		std::cout << "Nie wczytano czcionki" << std::endl;
		system("pause");
	}

	textC.setString("C: ");
	textV.setString("V: ");
	textGeneration.setString("Generation: ");
	C.setFont(font);
	V.setFont(font);
	textC.setFont(font);
	textV.setFont(font);
	textGeneration.setFont(font);
	generation.setFont(font);

	textC.setPosition(200.0f, 225.0f);
	textC.setFillColor(sf::Color::White);
	C.setPosition(290.0f, 225.0f);
	C.setFillColor(sf::Color::White);
	textV.setPosition(400.0f, 225.0f);
	textV.setFillColor(sf::Color::White);
	V.setPosition(490.0f, 225.0f);
	V.setFillColor(sf::Color::White);
	textGeneration.setPosition(0.0f, 500.0f);
	textGeneration.setFillColor(sf::Color::White);
	generation.setPosition(200.0f, 500.0f);
	generation.setFillColor(sf::Color::White);

	stateBarGreen.setFillColor(sf::Color::Green);
	stateBarRed.setFillColor(sf::Color::Red);
	upArrowC = new ArrowButton(sf::Color::Green, this->buttonRadius);
	downArrowC = new ArrowButton(sf::Color::Red, this->buttonRadius);
	upArrowV = new ArrowButton(sf::Color::Green, this->buttonRadius);
	downArrowV = new ArrowButton(sf::Color::Red, this->buttonRadius);

	upArrowC->setParameters(300.0f, 200.0f, true);
	//upArrowC->setPosition(300.0f, 200.0f);
	//upArrowC->setOrigin(10.0f, 10.0f);
	//upArrowC->setPointCount(3);
	//upArrowC->setRadius(5.0f);

	downArrowC->setParameters(300.0f, 300.0f, false);
	//downArrowC->setPosition(300.0f, 250.0f);
	//downArrowC->setOrigin(10.0f, 10.0f);
	//downArrowC->setRotation(180.0f);
	//downArrowC->setPointCount(3);
	//downArrowC->setRadius(5.0f);

	upArrowV->setParameters(500.0f, 200.0f, true);
	//upArrowV->setPosition(400.0f, 200.0f);
	//upArrowV->setOrigin(10.0f, 10.0f);
	//upArrowV->setPointCount(3);
	//upArrowV->setRadius(5.0f);

	downArrowV->setParameters(500.0f, 300.0f, false);
	//downArrowV->setPosition(400.0f, 250.0f);
	//downArrowV->setOrigin(10.0f, 10.0f);
	//downArrowV->setRotation(180.0f);
	//downArrowV->setPointCount(3);
	//downArrowV->setRadius(5.0f);
}


Scene::~Scene()
{
}

void Scene::setStateBarSize(float x, float y)
{
	stateBarSize.x = x;
	stateBarSize.y = y;

	stateBarGreen.setSize(sf::Vector2f(x, y));
	stateBarRed.setSize(sf::Vector2f(x, y));
}

void Scene::setStateBarPosition(float x, float y)
{
	stateBarPosition.x = x;
	stateBarPosition.y = y;

	stateBarGreen.setPosition(x, y);
	stateBarRed.setPosition(x, y);
}

void Scene::updateStateBar(float factor)
{
	stateBarRed.setSize(sf::Vector2f(stateBarSize.x * (factor /*/ Bird::maxAggr*/), stateBarSize.y));
	stateBarGreen.setSize(sf::Vector2f(stateBarSize.x * (1 - factor /*/ Bird::maxAggr*/), stateBarSize.y));
	stateBarGreen.setPosition(stateBarPosition.x + stateBarRed.getSize().x, stateBarPosition.y);
}

void Scene::setC(int C)
{
	this->C.setString(std::to_string(C));
}

void Scene::setV(int V)
{
	this->V.setString(std::to_string(V));
}

void Scene::setGeneration(int gen)
{
	this->generation.setString(std::to_string(gen));
}

void Scene::draw(sf::RenderWindow & window)
{
	window.draw(*upArrowC);
	window.draw(*upArrowV);
	window.draw(*downArrowC);
	window.draw(*downArrowV);

	window.draw(stateBarRed);
	window.draw(stateBarGreen);

	window.draw(textC);
	window.draw(textV);
	window.draw(C);
	window.draw(V);

	window.draw(textGeneration);
	window.draw(generation);
}

int Scene::checkButtonPressed(sf::Vector2f position)
{
	if (upArrowC->isPressed(position))
		return upC;
	if (downArrowC->isPressed(position))
		return downC;
	if (upArrowV->isPressed(position))
		return upV;
	if (downArrowV->isPressed(position))
		return downV;

	return 0;
}
