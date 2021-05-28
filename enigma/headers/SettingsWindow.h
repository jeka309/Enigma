#pragma once

#include <SFML/Graphics.hpp>

#include "Rotor.h"
#include "Selector.h"
#include "CommutationPanel.h"
#include "Coder.h"

class Block {

	float posX;
	float posY;

	float WIDTH = 600;
	float HEIGHT = 550;

	sf::RectangleShape background;
	sf::RectangleShape screws[4];

	const float SCREW_WIDTH = 40;
	const float SCREW_HEIGHT = 40;

	sf::Color backgroundColor = sf::Color(100, 100, 100);
	sf::Color screwColor = sf::Color::White;

public:

	Block(float posX = 0, float posY = 0);

	void SetPosition(float posX, float posY);
	void SetSize(float width, float height);

	void SetScrewTexture(const sf::Texture* texture);
	void SetBackgroundTexture(const sf::Texture* texture);
	void Draw(sf::RenderWindow& window);
};

class SettingsWindow {

	sf::RenderWindow* window = nullptr;

	const float WINDOW_WIDTH  = 1270;
	const float WINDOW_HEIGHT = 1000;

	EnigmaMachine* enigma = nullptr;

	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	sf::Texture screwTexture;
	sf::Texture blockBackgroundTexture;
	Block blockBacks[3];

	sf::Text blocks[3];

	Rotor** rotors = nullptr;

	Selector* rotorSettings[3];

	CommutationPanel* comPanel = nullptr;

	int jack1 = -1;

	const sf::Color windowClearColor = sf::Color(0, 51, 30);

	Button* buttonPressed = nullptr;

	void SyncRotors();

public:

	SettingsWindow(EnigmaMachine* enigma, sf::Font& textFont);

	void ButPressedCallback(float mouseX, float mouseY);
	void ButReleasedCallback();

	void Show();

	~SettingsWindow();
};