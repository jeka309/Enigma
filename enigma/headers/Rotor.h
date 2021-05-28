#pragma once

#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Coder.h"

class Rotor {

	float posX;
	float posY;

	const float WIDTH = 70;
	const float HEIGHT = 210;

	sf::RectangleShape background;
	sf::RectangleShape current;

	sf::Texture upButTexture;
	sf::Texture downButTexture;

	char lets[27] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	int cursor = 0;

	sf::Text lines[3];

	sf::Color backgroundColor = sf::Color(128, 128, 128);
	sf::Color outlineColor	  = sf::Color(200, 200, 200);

	void SetLines();

public:

	Button upButton;
	Button downButton;

	Rotor(sf::Font& textFont, float x = 0, float y = 0);
	
	void Draw(sf::RenderWindow& window);

	void SyncRotor(int16_t cur);

};