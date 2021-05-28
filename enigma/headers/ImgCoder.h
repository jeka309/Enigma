#pragma once

#include <SFML/Graphics.hpp>

#include "Coder.h"

class ImgCoder {

	sf::RenderWindow* window = nullptr;

	EnigmaMachine* enigma = nullptr;

	bool* isDone;

	sf::Image img;
	sf::Vector2u size;

	sf::Image* encImg = nullptr;
	sf::Texture* imgTexture = nullptr;
	sf::Sprite back;

	void Show();

	std::string RandName();
	std::string ExePath();

	friend void Encode(ImgCoder&);

public:

	ImgCoder(const char* img_path);
	~ImgCoder();
};