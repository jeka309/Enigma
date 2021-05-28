#pragma once

#include <SFML/Graphics.hpp>

class Button {

	float posX;
	float posY;

	const sf::Color col = sf::Color::Black;

	sf::RectangleShape rectangle;
	
	sf::CircleShape circle;
	bool circleShape = false;

	const float circlePosX	 = 7;
	const float circlePosY	 = 7;
	const float circleRadius = 28;

	sf::Texture buttonImg;

	sf::Text let;

	const float letPosX = 23;
	const float letPosY = 3;
	const float letSize = 40;

public:

	const float width = 70;
	const float height = 70;

	Button(float x = 0, float y = 0, const char* str = "a");

	void SetPosition(float x, float y);
	void SetFont(sf::Font& font);
	void SetString(const char* str);
	void SetColor(const sf::Color& col);
	void SetButTexture(sf::Texture* texture);
	void SetCircleShape(const sf::Color& color);

	bool inArea(float x, float y);

	void Draw(sf::RenderWindow& window);
};