#include "SettingsWindow.h"

Block::Block(float x, float y)
	: posX(x), posY(y)
{
	this->background.setFillColor(this->backgroundColor);
	this->background.setPosition(this->posX, this->posY);
	this->background.setSize(sf::Vector2f(this->WIDTH, this->HEIGHT));

	for (int i = 0; i < 4; ++i)
	{
		this->screws[i].setFillColor(this->screwColor);
		this->screws[i].setSize(sf::Vector2f(this->SCREW_WIDTH, this->SCREW_HEIGHT));
	}

	float margin = 10;
	this->screws[0].setPosition((this->posX + margin), (this->posY + margin));
	this->screws[1].setPosition((this->posX + this->WIDTH - margin - this->SCREW_WIDTH), (this->posY + margin));
	this->screws[2].setPosition((this->posX + margin), (this->posY + this->HEIGHT - margin - this->SCREW_HEIGHT));
	this->screws[3].setPosition((this->posX + this->WIDTH - margin - this->SCREW_WIDTH), (this->posY + this->HEIGHT - margin - this->SCREW_HEIGHT));
}

void Block::SetSize(float w, float h)
{
	this->WIDTH = w;
	this->HEIGHT = h;

	this->background.setSize(sf::Vector2f(w, h));

	float margin = 10;
	this->screws[0].setPosition((this->posX + margin), (this->posY + margin));
	this->screws[1].setPosition((this->posX + this->WIDTH - margin - this->SCREW_WIDTH), (this->posY + margin));
	this->screws[2].setPosition((this->posX + margin), (this->posY + this->HEIGHT - margin - this->SCREW_HEIGHT));
	this->screws[3].setPosition((this->posX + this->WIDTH - margin - this->SCREW_WIDTH), (this->posY + this->HEIGHT - margin - this->SCREW_HEIGHT));
}

void Block::SetPosition(float x, float y)
{
	this->posX = x;
	this->posY = y;

	float margin = 10;
	this->background.setPosition(this->posX, this->posY);
	this->screws[0].setPosition((this->posX + margin), (this->posY + margin));
	this->screws[1].setPosition((this->posX + this->WIDTH - margin - this->SCREW_WIDTH), (this->posY + margin));
	this->screws[2].setPosition((this->posX + margin), (this->posY + this->HEIGHT - margin - this->SCREW_HEIGHT));
	this->screws[3].setPosition((this->posX + this->WIDTH - margin - this->SCREW_WIDTH), (this->posY + this->HEIGHT - margin - this->SCREW_HEIGHT));
}

void Block::SetScrewTexture(const sf::Texture* texture)
{
	for (int i = 0; i < 4; ++i)
	{
		this->screws[i].setTexture(texture);
	}
}

void Block::SetBackgroundTexture(const sf::Texture* texture)
{
	this->background.setTexture(texture);
}

void Block::Draw(sf::RenderWindow& window)
{
	window.draw(this->background);
	for (int i = 0; i < 4; ++i)
		window.draw(this->screws[i]);
}






SettingsWindow::SettingsWindow(EnigmaMachine* enigma, sf::Font& textFont)
	: enigma(enigma)
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->WINDOW_WIDTH, this->WINDOW_HEIGHT), "Settings", sf::Style::Close);
	this->window->setFramerateLimit(60);

	this->screwTexture.loadFromFile("./resources/screw.png");
	this->screwTexture.setRepeated(false);
	this->screwTexture.setSmooth(true);
	this->blockBackgroundTexture.loadFromFile("./resources/steel.png");
	this->blockBackgroundTexture.setRepeated(false);
	this->blockBackgroundTexture.setSmooth(true);

	this->backgroundTexture.loadFromFile("./resources/barkhat.jpg");
	this->backgroundTexture.setRepeated(false);
	this->backgroundTexture.setSmooth(true);

	this->background.setFillColor(sf::Color(128, 128, 128));
	this->background.setPosition(0, 0);
	this->background.setSize(sf::Vector2f(this->WINDOW_WIDTH, this->WINDOW_HEIGHT));
	this->background.setTexture(&(this->backgroundTexture));

	for (int i = 0; i < 3; ++i)
	{
		this->blockBacks[i].SetScrewTexture(&(this->screwTexture));
		this->blockBacks[i].SetBackgroundTexture(&(this->blockBackgroundTexture));
	}

	this->blockBacks[0].SetPosition(20, 20);
	this->blockBacks[1].SetPosition(650, 20);
	this->blockBacks[2].SetPosition(20, 590);
	this->blockBacks[2].SetSize(1230, 390);

	int x = 0, y = 120;
	this->rotors = new Rotor * [3];
	for (int i = 0; i < 3; ++i)
	{
		x = 130 + i * 150;
		this->rotors[i] = new Rotor(textFont, x, y);
	}

	for (int i = 0; i < 3; ++i)
	{
		x = 760 + i * 150;
		this->rotorSettings[i] = new Selector(textFont, x, y);
	}

	for (int i = 0; i < 3; ++i)
	{
		this->rotorSettings[i]->SetCursor(this->enigma->settings[i]);
	}

	for (int i = 0; i < 3; ++i)
	{
		this->blocks[i].setFont(textFont);
		this->blocks[i].setCharacterSize(30);
	}

	this->blocks[0].setString("Rotors initial positions");
	this->blocks[0].setPosition(sf::Vector2f(120, 30));

	this->blocks[1].setString("Rotors settings");
	this->blocks[1].setPosition(sf::Vector2f(820, 30));

	this->comPanel = new CommutationPanel(textFont, 100, 630);
	this->comPanel->SyncJacks(*(this->enigma));

	this->SyncRotors();
}

SettingsWindow::~SettingsWindow()
{
	delete this->window;
}

void SettingsWindow::SyncRotors()
{
	for (int i = 0; i < 3; ++i)
	{
		this->rotors[i]->SyncRotor(this->enigma->GetCur(static_cast<EnigmaMachine::Rotors>(i)));
	}
}

void SettingsWindow::Show()
{
	sf::Event event;
	while (this->window->isOpen())
	{
		while (this->window->pollEvent(event))
		{
			switch (event.type)
			{

			case sf::Event::Closed:
				this->window->close();
				break;

			case sf::Event::MouseButtonPressed:
				this->ButPressedCallback(event.mouseButton.x, event.mouseButton.y);
				break;

			case sf::Event::MouseButtonReleased:
				this->ButReleasedCallback();
				break;

			default:
				break;

			}
		}

		this->window->clear(this->windowClearColor);
		this->window->draw(this->background);

		for (int i = 0; i < 3; ++i)
			this->blockBacks[i].Draw(*(this->window));

		this->comPanel->Draw(*(this->window));

		for (int i = 0; i < 3; ++i)
			this->rotors[i]->Draw(*(this->window));

		for (int i = 0; i < 3; ++i)
			this->rotorSettings[i]->Draw(*(this->window));

		for (int i = 0; i < 3; ++i)
			window->draw(this->blocks[i]);

		this->window->display();
	}
}

void SettingsWindow::ButPressedCallback(float mouseX, float mouseY)
{
	if (this->buttonPressed != nullptr)
		return;

	bool flag = true;

	for (int i = 0; i < 3 && flag; ++i)
	{
		if (this->rotors[i]->upButton.inArea(mouseX, mouseY))
		{
			flag = false;

			buttonPressed = &this->rotors[i]->upButton;
			this->enigma->ShiftDown(static_cast<EnigmaMachine::Rotors>(i));
			this->SyncRotors();
		}
		else if (this->rotors[i]->downButton.inArea(mouseX, mouseY))
		{
			flag = false;

			buttonPressed = &this->rotors[i]->downButton;
			this->enigma->ShiftUp(static_cast<EnigmaMachine::Rotors>(i));
			this->SyncRotors();
		}
	}

	for (int i = 0; i < 3 && flag; ++i)
	{
		if (this->rotorSettings[i]->upButton.inArea(mouseX, mouseY))
		{
			flag = false;
			buttonPressed = &this->rotorSettings[i]->upButton;
			this->rotorSettings[i]->ShiftUp();
			this->enigma->SetSetting(static_cast<EnigmaMachine::Rotors>(i), this->rotorSettings[i]->GetCurrent() - 'A');
		}
		else if (this->rotorSettings[i]->downButton.inArea(mouseX, mouseY))
		{
			flag = false;
			buttonPressed = &this->rotorSettings[i]->downButton;
			this->rotorSettings[i]->ShiftDown();
			this->enigma->SetSetting(static_cast<EnigmaMachine::Rotors>(i), this->rotorSettings[i]->GetCurrent() - 'A');
		}
	}

	if (flag)
	{
		int tmp = this->comPanel->isClicked(mouseX, mouseY);
		if (tmp != -1)
		{
			char* coms = this->enigma->GetCommutations();

			if (coms[tmp] == 0)
			{
				if (this->jack1 == -1)
				{
					jack1 = tmp;

					this->comPanel->SetJackColor(tmp, sf::Color::White);
				}
				else
				{
					this->enigma->SetCommutation(jack1 + 'a', tmp + 'a');
					this->comPanel->SyncJacks(*(this->enigma));

					jack1 = -1;
				}
			}
			else {
				this->enigma->SetCommutation(tmp + 'a', tmp + 'a');
				this->comPanel->SyncJacks(*(this->enigma));

				jack1 = -1;
			}

		}

		flag = false;
	}

	if(this->buttonPressed)
		this->buttonPressed->SetColor(sf::Color(128, 128, 128));
}

void SettingsWindow::ButReleasedCallback()
{
	if (!(this->buttonPressed))
		return;

	this->buttonPressed->SetColor(sf::Color::White);
	this->buttonPressed = nullptr;
}