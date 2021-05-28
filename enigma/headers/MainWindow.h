#pragma once

#include <SFML/Graphics.hpp>

#include "SettingsWindow.h"
#include "Keyboard.h"
#include "Coder.h"

class MainWindow {

	sf::RenderWindow* window = nullptr;

	const float WINDOW_WIDTH  = 1727;
	const float WINDOW_HEIGHT = 810;

	sf::Texture backgroundTexture;
	sf::Sprite background;

	Keyboard* lamps = nullptr;
	Keyboard* buttons = nullptr;
	sf::Font kbFont;

	sf::Texture settingsTexture;
	Button settingsButton;

	sf::Texture buttonTexture;
	sf::Texture lampTexture;

	sf::Keyboard::Key keyPressed = sf::Keyboard::Key::Unknown;
	sf::Keyboard::Key keyColored = sf::Keyboard::Key::Unknown;

	const sf::Color lampColor		   = sf::Color(50, 50, 50);
	const sf::Color lampLightColor	   = sf::Color(180, 180, 0);
	const sf::Color buttonColor		   = sf::Color::White;
	const sf::Color buttonPressedColor = sf::Color(128, 128, 128);
	const sf::Color windowClearColor   = sf::Color(155, 100, 103);

	EnigmaMachine enigma;

	bool settingsIsOpened = false;

public:

	MainWindow();

	void KeyPressedCallback(sf::Keyboard::Key key);
	void KeyReleasedCallback(sf::Keyboard::Key key);
	void Show();

	~MainWindow();
};