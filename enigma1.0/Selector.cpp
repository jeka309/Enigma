#include "Selector.h"

Selector::Selector(sf::Font& textFont, float x, float y)
	: posX(x), posY(y)
{
	this->lets_num = 26;
	this->lets = new char[this->lets_num];

	for (int i = 0; i < this->lets_num; ++i)
	{
		this->lets[i] = i + 'A';
	}

	this->background.setPosition(this->posX, this->posY);
	this->background.setSize(sf::Vector2f(this->WIDTH, this->HEIGHT));
	this->background.setFillColor(this->backgroundColor);
	this->background.setOutlineColor(this->outlineColor);
	this->background.setOutlineThickness(5);

	this->current.setPosition(this->posX, this->posY + (this->HEIGHT / 3));
	this->current.setSize(sf::Vector2f(this->WIDTH, this->HEIGHT / 3));
	this->current.setFillColor(sf::Color::Transparent);
	this->current.setOutlineColor(sf::Color(220, 220, 220));
	this->current.setOutlineThickness(10);

	for (int i = 0; i < 3; ++i)
	{
		this->lines[i].setFont(textFont);
		this->lines[i].setCharacterSize(50);
	}

	float linesX = 20;

	this->lines[0].setPosition(this->posX + linesX, this->posY);
	this->lines[1].setPosition(this->posX + linesX, this->posY + (this->HEIGHT / 3));
	this->lines[2].setPosition(this->posX + linesX, this->posY + 2 * (this->HEIGHT / 3));

	this->SetLines();

	this->upButTexture.loadFromFile("./resources/rotorbutup.png");
	this->upButTexture.setRepeated(false);
	this->upButTexture.setSmooth(true);

	this->upButton.SetButTexture(&(this->upButTexture));
	this->upButton.SetColor(sf::Color::White);
	//this->upButton.SetSize(70, 70);
	this->upButton.SetPosition(this->posX + 3, this->posY + 230);

	this->downButTexture.loadFromFile("./resources/rotorbutdown.png");
	this->downButTexture.setRepeated(false);
	this->downButTexture.setSmooth(true);

	this->downButton.SetButTexture(&(this->downButTexture));
	this->downButton.SetColor(sf::Color::White);
	//this->downButton.SetSize(70, 70);
	this->downButton.SetPosition(this->posX + 3, this->posY + 300);
}

void Selector::SetLines()
{
	if ((this->cursor - 1) < 0)
		this->lines[0].setString(this->lets[this->lets_num - 1]);
	else
		this->lines[0].setString(this->lets[this->cursor - 1]);

	this->lines[1].setString(this->lets[this->cursor]);
	this->lines[2].setString(this->lets[(this->cursor + 1) % 26]);
}

void Selector::SetAlphabet(const char* string, size_t nmemb)
{
	if (!string || !nmemb)
		return;

	if (this->lets)
	{
		delete this->lets;

		this->lets = new char[nmemb];
		this->lets_num = nmemb;
	}

	for (int i = 0; i < nmemb; ++i)
	{
		this->lets[i] = string[i];
	}
}

void Selector::SetCursor(uint16_t offset)
{
	this->cursor = offset % this->lets_num;

	this->SetLines();
}

void Selector::ShiftUp()
{
	if (this->cursor - 1 < 0)
		this->cursor = this->lets_num - 1;
	else
		this->cursor--;

	this->SetLines();
}

void Selector::ShiftDown()
{
	this->cursor = (this->cursor + 1) % this->lets_num;

	this->SetLines();
}

char Selector::GetCurrent()
{
	return this->lets[this->cursor];
}

void Selector::Draw(sf::RenderWindow& window)
{
	window.draw(this->background);

	for (int i = 0; i < 3; ++i)
	{
		window.draw(this->lines[i]);
	}

	window.draw(this->current);

	this->upButton.Draw(window);
	this->downButton.Draw(window);
}