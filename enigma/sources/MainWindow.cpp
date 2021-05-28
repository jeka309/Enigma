#include "MainWindow.h"

MainWindow::MainWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->WINDOW_WIDTH, this->WINDOW_HEIGHT), "Enigma", sf::Style::Close);
	this->window->setFramerateLimit(60);

	this->enigma.SetRotor("ekmflgdqvzntowyhxuspaibrcjq", EnigmaMachine::Rotors::FIRST);
	this->enigma.SetRotor("ajdksiruxblhwtmcqgznpyfvoee", EnigmaMachine::Rotors::SECOND);
	this->enigma.SetRotor("bdfhjlcprtxvznyeiwgakmusqov", EnigmaMachine::Rotors::THIRD);

	this->enigma.SetReflector("yruhqsldpxngokmiebfzcwvjat");

	this->kbFont.loadFromFile("./resources/font.ttf");

	this->buttonTexture.loadFromFile("./resources/buttonNotPressed.png");
	this->buttonTexture.setSmooth(true);
	this->buttonTexture.setRepeated(false);

	this->lampTexture.loadFromFile("./resources/buttonPressed.png");
	this->lampTexture.setSmooth(true);
	this->lampTexture.setRepeated(false);

	this->lamps = new Keyboard(this->kbFont, 190, 100);
	this->buttons = new Keyboard(this->kbFont, 190, 440);

	for (int i = 0; i < 27; ++i)
	{
		this->lamps->SetButtonTexture(i, &(this->lampTexture));
		this->lamps->SetButtonColor(i, this->buttonColor);
		this->lamps->SetButtonCircleShape(i, this->lampColor);

		this->buttons->SetButtonTexture(i, &(this->buttonTexture));
		this->buttons->SetButtonColor(i, this->buttonColor);
	}

	this->backgroundTexture.loadFromFile("./resources/background.png");
	this->backgroundTexture.setSmooth(true);
	this->backgroundTexture.setRepeated(false);

	this->background.setTexture(this->backgroundTexture);
	this->background.setColor(sf::Color::White);

	this->settingsTexture.loadFromFile("./resources/buttonSettings.png");
	this->settingsTexture.setRepeated(false);
	this->settingsTexture.setSmooth(true);

	this->settingsButton.SetButTexture(&(this->settingsTexture));
	this->settingsButton.SetColor(sf::Color::White);
	this->settingsButton.SetPosition(60, 370);
}

void MainWindow::KeyPressedCallback(sf::Keyboard::Key key)
{
	if (this->keyPressed != sf::Keyboard::Key::Unknown)
		return;

	if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z)
	{
		this->keyColored = static_cast<sf::Keyboard::Key> (this->enigma.Encode(key + 'a') - 'a');
		this->keyPressed = key;

		this->buttons->SetButtonColor(this->keyPressed, this->buttonPressedColor);
		this->lamps->SetButtonCircleShape(this->keyColored, this->lampLightColor);
	}
	else if (key == sf::Keyboard::Space)
	{
		this->keyColored = sf::Keyboard::Space;
		this->keyPressed = key;

		this->buttons->SetButtonColor(26, this->buttonPressedColor);
		this->lamps->SetButtonCircleShape(26, this->lampLightColor);
	}
	else if (key == 27)
	{
		this->settingsButton.SetColor(this->buttonPressedColor);

		this->keyPressed = static_cast<sf::Keyboard::Key>(27);
	}
}

void MainWindow::KeyReleasedCallback(sf::Keyboard::Key key)
{
	if (this->keyPressed != key)
		return;

	if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z)
	{
		this->buttons->SetButtonColor(this->keyPressed, this->buttonColor);
		this->lamps->SetButtonCircleShape(this->keyColored, this->lampColor);

		this->keyPressed = sf::Keyboard::Key::Unknown;
		this->keyColored = sf::Keyboard::Key::Unknown;
	}
	else if (key == sf::Keyboard::Space)
	{
		this->buttons->SetButtonColor(26, this->buttonColor);
		this->lamps->SetButtonCircleShape(26, this->lampColor);

		this->keyPressed = sf::Keyboard::Key::Unknown;
		this->keyColored = sf::Keyboard::Key::Unknown;
	}
	else if (key == 27)
	{
		this->settingsButton.SetColor(this->buttonColor);

		this->keyPressed = sf::Keyboard::Key::Unknown;
	}
}

void MainWindow::Show()
{
	int but = -1;
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
				but = this->buttons->ButtonClicked(event.mouseButton.x, event.mouseButton.y);
				if (but != -1)
				{
					if (but == 26)
						this->KeyPressedCallback(sf::Keyboard::Key::Space);
					else
						this->KeyPressedCallback(static_cast<sf::Keyboard::Key>(but));
				}
				else if (this->settingsButton.inArea(event.mouseButton.x, event.mouseButton.y))
				{
					this->KeyPressedCallback(static_cast<sf::Keyboard::Key>(27));

					this->settingsIsOpened = true;
				}

				break;

			case sf::Event::MouseButtonReleased:
				this->KeyReleasedCallback(this->keyPressed);
				break;

			case sf::Event::KeyPressed:
				this->KeyPressedCallback(event.key.code);
				break;

			case sf::Event::KeyReleased:
				this->KeyReleasedCallback(event.key.code);
				break;

			default:
				break;

			}
		}

		this->window->clear(this->windowClearColor);
		this->window->draw(this->background);

		this->lamps->Draw(*(this->window));
		this->buttons->Draw(*(this->window));
		this->settingsButton.Draw(*(this->window));

		this->window->display();

		if (this->settingsIsOpened)
		{
			SettingsWindow sw(&(this->enigma), this->kbFont);
			sw.Show();

			this->settingsIsOpened = false;
		}
	}
}

MainWindow::~MainWindow()
{
	delete this->lamps;
	delete this->buttons;
	delete this->window;
}