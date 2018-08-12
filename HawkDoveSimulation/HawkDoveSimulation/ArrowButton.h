#ifndef _ARROWBUTTON
#define _ARROWBUTTON

#include <SFML\Graphics.hpp>

class ArrowButton :
	public sf::CircleShape
{
public:
	ArrowButton(sf::Color, float);
	~ArrowButton();

	void setParameters(float, float, bool);
	bool isPressed(sf::Vector2f);
};

#endif