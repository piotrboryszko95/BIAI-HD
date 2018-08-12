#include "ArrowButton.h"



ArrowButton::ArrowButton(sf::Color color, float radius) : sf::CircleShape(radius, 3)
{
	//this->setPointCount(3);
	this->setFillColor(color);
}


ArrowButton::~ArrowButton()
{
}

void ArrowButton::setParameters(float x, float y, bool facingUp)
{
	this->setOrigin(this->getRadius(), this->getRadius());
	this->setPosition(x, y);
	if (!facingUp)
		this->setRotation(180);
}

bool ArrowButton::isPressed(sf::Vector2f pos)
{
	if (abs(this->getPosition().x - pos.x) <= this->getRadius() &&
		abs(this->getPosition().y - pos.y) <= this->getRadius())
		return true;
	else
		return false;
}
