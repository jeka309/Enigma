#include "CommutationPanel.h"

#include <cmath>

Jack::Jack(sf::Font& font, char let, float x, float y, float rad)
	: posX(x), posY(y), radius(rad)
{
	this->let.setFont(font);
	this->let.setString(let);
	this->let.setPosition(sf::Vector2f(this->posX, this->posY));
	this->let.setCharacterSize(50);

	this->jack.setFillColor(this->defaultJackColor);
	this->jack.setRadius(rad);
	this->jack.setOutlineThickness(rad / 2);
	this->jack.setOutlineColor(sf::Color(180, 180, 180));

	this->circleX = this->posX + 55;
	this->circleY = this->posY + 25;

	this->jack.setPosition(this->circleX, this->circleY);
}

void Jack::Draw(sf::RenderWindow& window)
{
	window.draw(this->let);
	window.draw(this->jack);
}

bool Jack::inArea(float x, float y)
{
	return ((x > this->circleX) && (x < this->circleX + 20) && (y > this->circleY) && (y < this->circleY + 20));
}

void Jack::SetColor(const sf::Color& col)
{
	this->jack.setFillColor(col);
}






CommutationPanel::CommutationPanel(sf::Font& font, float x, float y)
	: posX(x), posY(y)
{
	this->jacks = new Jack * [this->JACKS_COUNT];

	for (int i = 0, x = 0, y = -1; i < this->JACKS_COUNT; ++i, ++x)
	{
		if (i % ((int)this->JACKS_COUNT / 3) == 0)
		{
			y++;
			x = 0;
		}

		this->jacks[i] = new Jack(font, i + 'A', this->posX + x * 140, this->posY + y * 70, 10);
	}

	for (int i = 0; i < 26; ++i)
	{
		if (jacksColors[i])
		{
			SetJackColor(i, jacksColors[i]->col);
		}
	}
}

_color* CommutationPanel::findColor()
{
	for (int i = 0; i < 13; ++i)
	{
		if (!(uniqColors[i].isUsed))
			return &(uniqColors[i]);
	}

	return nullptr;
}

void CommutationPanel::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < this->JACKS_COUNT; ++i)
		this->jacks[i]->Draw(window);
}

int CommutationPanel::isClicked(float mouseX, float mouseY)
{
	for (int i = 0; i < this->JACKS_COUNT; ++i)
	{
		if (this->jacks[i]->inArea(mouseX, mouseY))
			return i;
	}

	return -1;
}

void CommutationPanel::SyncJacks(EnigmaMachine& enigma)
{
	char* coms = enigma.GetCommutations();

	for (int i = 0; i < 26; ++i)
	{
		if (coms[i] == 0 && jacksColors[i] != nullptr)
		{
			jacksColors[i]->isUsed = false;
			jacksColors[i] = nullptr;
			SetJackColor(i, sf::Color::Black);
		}
		else if (coms[i] == 0 && jacksColors[i] == nullptr)
		{
			SetJackColor(i, sf::Color::Black);
		}
		else if (coms[i] != 0 && jacksColors[i] != nullptr)
		{
			if (jacksColors[i] != jacksColors[coms[i] - 'a'])
			{
				jacksColors[coms[i] - 'a'] = nullptr;
			}
		}
		else if (coms[i] != 0 && jacksColors[i] == nullptr)
		{
			if (jacksColors[coms[i] - 'a'] != nullptr)
			{
				jacksColors[i] = jacksColors[coms[i] - 'a'];
			}
			else
			{
				_color* col = findColor();
				col->isUsed = true;

				jacksColors[i] = col;
				jacksColors[coms[i] - 'a'] = col;

				this->SetJackColor(i, col->col);
				this->SetJackColor(coms[i] - 'a', col->col);
			}
		}
	}
}

void CommutationPanel::SetJackColor(uint16_t pos, const sf::Color& col)
{
	if (pos >= this->JACKS_COUNT)
		return;

	this->jacks[pos]->SetColor(col);
}