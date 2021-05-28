#include "Keyboard.h"

Keyboard::Keyboard(sf::Font& font, float x, float y)
	: posX(x), posY(y)
{
	char str[2] = " ";
	for (int i = 0, ch = (int)'a'; i < (this->nFRow + this->nSRow + this->nTRow); ++i, ++ch)
	{
		this->buttons[i].SetFont(font);

		str[0] = ch;
		this->buttons[i].SetString(str);
	}
	this->buttons[this->nFRow + this->nSRow + this->nTRow - 1].SetString("_");

	float sPosX = this->posX;
	float sPosY = this->posY;

	float spacing = 75;

	for (int i = 0; i < this->nFRow; ++i)
	{
		this->buttons[i].SetPosition(sPosX, sPosY);

		sPosX += (this->buttons[i].width + spacing);
	}

	sPosX = this->posX + 60;
	sPosY += (this->buttons[0].height + 30);

	spacing = 75;

	for (int i = this->nFRow; i < (this->nFRow + this->nSRow); ++i)
	{
		this->buttons[i].SetPosition(sPosX, sPosY);

		sPosX += (this->buttons[i].width + spacing);
	}

	sPosX = this->posX + 120;
	sPosY += (this->buttons[0].height + 30);

	spacing = 75;

	for (int i = (this->nFRow + this->nSRow); i < (this->nFRow + this->nSRow + this->nTRow); ++i)
	{
		this->buttons[i].SetPosition(sPosX, sPosY);

		sPosX += (this->buttons[i].width + spacing);
	}
}

void Keyboard::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < (this->nFRow + this->nSRow + this->nTRow); ++i)
	{
		this->buttons[i].Draw(window);
	}
}

void Keyboard::SetButtonColor(sf::Uint32 pos, const sf::Color& col)
{
	this->buttons[pos].SetColor(col);
}

void Keyboard::SetButtonTexture(sf::Uint32 pos, sf::Texture* texture)
{
	if (pos >= (this->nFRow + this->nSRow + this->nTRow))
		return;

	this->buttons[pos].SetButTexture(texture);
}

void Keyboard::SetButtonCircleShape(sf::Uint32 pos, const sf::Color& color)
{
	if (pos >= (this->nFRow + this->nSRow + this->nTRow))
		return;

	this->buttons[pos].SetCircleShape(color);
}

int Keyboard::ButtonClicked(float mouseX, float mouseY)
{
	for (int i = 0; i < (this->nFRow + this->nSRow + this->nTRow); ++i)
	{
		if (this->buttons[i].inArea(mouseX, mouseY))
			return i;
	}

	return -1;
}