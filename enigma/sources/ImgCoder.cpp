#include "ImgCoder.h"

#include <Windows.h>
#include <random>

void Encode(ImgCoder& coder)
{
	sf::Color col;
	for (int i = 0; i < coder.size.x; ++i)
	{
		for (int j = 0; j < coder.size.y; ++j)
		{
			col = coder.img.getPixel(i, j);

			col = coder.enigma->EncodePixel(col);

			coder.encImg->setPixel(i, j, col);
			coder.imgTexture->loadFromImage(*coder.encImg);
		}
	}

	*coder.isDone = true;
}

std::string ImgCoder::RandName()
{
	std::random_device r;
	std::default_random_engine el(r());
	std::uniform_int_distribution<int> dist(10, 30);

	size_t sz = dist(el);

	std::string res = "";
	
	std::uniform_int_distribution<int> dist1('a', 'z');

	char ch;
	for (int i = 0; i < sz; ++i)
	{
		ch = dist1(el);
		res += ch;
	}

	res += ".png";

	return res;
}

std::string ImgCoder::ExePath()
{
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");

	return std::string(buffer).substr(0, pos);
}

ImgCoder::ImgCoder(const char* path)
{
	if (!this->img.loadFromFile(path))
	{
		return;
	}

	this->isDone = new bool(false);

	this->enigma = new EnigmaMachine(16);
	this->imgTexture = new sf::Texture;

	this->enigma->SetRotor("gohikjablcpdenfmc", EnigmaMachine::Rotors::FIRST);
	this->enigma->SetRotor("pedcnabohmgflijkb", EnigmaMachine::Rotors::SECOND);
	this->enigma->SetRotor("nfhgokpjiabmcedlf", EnigmaMachine::Rotors::THIRD);

	this->enigma->SetReflector("ejhdaigcfbmokpln");

	this->encImg = new sf::Image(this->img);

	this->size = this->img.getSize();

	this->window = new sf::RenderWindow(sf::VideoMode(this->size.x, this->size.y), "img", sf::Style::Close);
	this->window->setFramerateLimit(30);

	this->imgTexture->loadFromImage(*this->encImg);
	this->imgTexture->setRepeated(false);
	this->imgTexture->setSmooth(false);

	this->back.setTexture(*this->imgTexture);
	this->back.setPosition(sf::Vector2f(0, 0));

	sf::Thread thr(&Encode, *(this));
	thr.launch();

	this->Show();
}

ImgCoder::~ImgCoder()
{
}

void ImgCoder::Show()
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

			default:
				break;

			}
		}

		if (*this->isDone)
		{
			this->encImg->saveToFile(this->ExePath() + "/encoded/" + this->RandName());
			this->window->close();
			return;
		}

		this->window->clear(sf::Color::White);

		this->window->draw(this->back);

		this->window->display();
	}
}