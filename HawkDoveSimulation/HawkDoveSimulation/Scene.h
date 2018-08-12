#ifndef _SCENE
#define _SCENE

#include "ArrowButton.h"
#include <SFML\Graphics.hpp>
#include <iostream>

class Scene
{
public:
	Scene(float buttonRadius);
	~Scene();

	void setStateBarSize(float x, float y);
	void setStateBarPosition(float x, float y);
	void updateStateBar(float factor);
	void setC(int C);
	void setV(int V);
	void setGeneration(int gen);
	void draw(sf::RenderWindow&);
	int checkButtonPressed(sf::Vector2f);

private:
	sf::Vector2f stateBarSize;
	sf::Vector2f stateBarPosition;
	sf::Font font;
	sf::Text textC;
	sf::Text textV;
	sf::Text textGeneration;
	sf::Text C;
	sf::Text V;
	sf::Text generation;
	sf::RectangleShape stateBarRed;
	sf::RectangleShape stateBarGreen;
	ArrowButton * upArrowC;
	ArrowButton * downArrowC;
	ArrowButton * upArrowV;
	ArrowButton * downArrowV;

	float buttonRadius;

public:
	static const enum button{ upC = 1, downC = 2, upV = 3, downV = 4};
};

#endif