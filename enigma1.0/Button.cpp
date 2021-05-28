#include "Button.h"

Button::Button(float x, float y, const char* str)
	: posX(x), posY(y)
{
	this->rectangle.setFillColor(this->col);
	this->rectangle.setPosition(sf::Vector2f(this->posX, this->posY));
	this->rectangle.setSize(sf::Vector2f(this->width, this->height));

	this->let.setPosition(this->posX + this->letPosX, this->posY + this->letPosY);
	this->let.setFillColor(sf::Color::White);
	this->let.setCharacterSize(this->letSize);
	this->let.setString(str);
}

void Button::Draw(sf::RenderWindow& window)
{
	if (this->circleShape)
		window.draw(this->circle);

	window.draw(this->rectangle);
	window.draw(this->let);
}

void Button::SetPosition(float x, float y)
{
	this->posX = x;
	this->posY = y;

	this->rectangle.setPosition(sf::Vector2f(this->posX, this->posY));
	this->let.setPosition(this->posX + this->letPosX, this->posY + this->letPosY);
}

void Button::SetFont(sf::Font& font)
{
	this->let.setFont(font);
}

void Button::SetString(const char* str)
{
	this->let.setString(str);
}

void Button::SetColor(const sf::Color& col)
{
	this->rectangle.setFillColor(col);
}

void Button::SetButTexture(sf::Texture* texture)
{
	this->rectangle.setTexture(texture);
}

void Button::SetCircleShape(const sf::Color& color)
{
	this->circleShape = true;
	this->circle.setFillColor(color);
	this->circle.setRadius(this->circleRadius);
	this->circle.setPosition(sf::Vector2f(this->posX + this->circlePosX, this->posY + this->circlePosY));
}

bool Button::inArea(float x, float y)
{
	return (x > this->posX&& x < (this->posX + this->width) && y > this->posY && y < (this->posY + this->height));
}