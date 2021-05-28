#pragma once

#include <SFML/Graphics.hpp>

#include "Coder.h"

class Jack {

	sf::Text let;

	sf::CircleShape jack;
	
	float posX;
	float posY;

	float circleX;
	float circleY;

	float radius;

	sf::Color defaultJackColor = sf::Color::Black;

public:

	Jack(sf::Font& font, char let = ' ', float x = 0, float y = 0, float rad = 5);

	void Draw(sf::RenderWindow& window);
	bool inArea(float mouseX, float mouseY);

	void SetColor(const sf::Color& col);

};

struct _color {
	sf::Color col = { sf::Color::Black };
	bool isUsed = false;
};

static _color* jacksColors[26] = { nullptr };
static _color uniqColors[13] = {
	{ sf::Color(255, 0, 0) },
	{ sf::Color(0, 255, 0) },
	{ sf::Color(0, 0, 255) },
	{ sf::Color(255, 255, 0) },
	{ sf::Color(255, 0, 255) },
	{ sf::Color(0, 255, 255) },
	{ sf::Color(48, 0, 98) },
	{ sf::Color(47, 79, 79) },
	{ sf::Color(80, 200, 120) },
	{ sf::Color(223, 115, 255) },
	{ sf::Color(219, 112, 147) },
	{ sf::Color(158, 185, 212) },
	{ sf::Color(183, 65, 14) }
};

class CommutationPanel {

	const float JACKS_COUNT = 26;
	Jack** jacks;
	
	float posX;
	float posY;

	_color* findColor();

public:

	CommutationPanel(sf::Font& font, float x = 0, float y = 0);

	void SyncJacks(EnigmaMachine& enigma);

	void Draw(sf::RenderWindow& window);
	int isClicked(float mouseX, float mouseY);
	void SetJackColor(uint16_t pos, const sf::Color& col);

};