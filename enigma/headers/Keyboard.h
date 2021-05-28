#pragma once

#include <SFML/Graphics.hpp>

#include "Button.h"

class Keyboard {

	float posX;
	float posY;
	
	static const sf::Uint32 nFRow = 10;
	static const sf::Uint32 nSRow = 9;
	static const sf::Uint32 nTRow = 8;

	Button buttons[nFRow + nSRow + nTRow];

public:

	Keyboard(sf::Font& font, float x = 0, float y = 0);

	void Draw(sf::RenderWindow& window);
	void SetButtonColor(sf::Uint32 pos, const sf::Color& col);
	void SetButtonTexture(sf::Uint32 pos, sf::Texture* texture);
	void SetButtonCircleShape(sf::Uint32 pos, const sf::Color& color);

	int ButtonClicked(float mouseX, float mouseY);
};