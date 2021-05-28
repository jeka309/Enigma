#include "Coder.h"

#include <string>
#include <cmath>

EnigmaMachine::EnigmaMachine(size_t rotor_len, size_t rotors_count)
	: ROTOR_LEN(rotor_len), ROTORS_COUNT(rotors_count)
{
	this->initialRotors = new char* [this->ROTORS_COUNT];
	this->rotors = new char* [this->ROTORS_COUNT];

	for (int i = 0; i < this->ROTORS_COUNT; ++i)
	{
		this->initialRotors[i] = new char[this->ROTOR_LEN + 1];
		this->rotors[i] = new char[this->ROTOR_LEN + 1];
	}

	this->reflector = new char[this->ROTOR_LEN];

	this->commutations = new char[this->ROTOR_LEN];
	for (int i = 0; i < this->ROTOR_LEN; ++i)
		this->commutations[i] = 0;

	this->cursors = new int16_t[this->ROTORS_COUNT];
	for (int i = 0; i < this->ROTORS_COUNT; ++i)
		this->cursors[i] = 0;
}

EnigmaMachine::~EnigmaMachine()
{

}

int EnigmaMachine::Find(const char* rotor, char let)
{
	for (int i = 0; i < this->ROTOR_LEN; ++i)
	{
		if (rotor[i] == let)
			return i;
	}

	return -1;
}

char EnigmaMachine::CycleSum(char left, char right)
{
	if (left + right < 0)
	{
		return this->CycleSum(this->ROTOR_LEN, (left + right));
	}
	
	return (left + right) % this->ROTOR_LEN;
}

std::string EnigmaMachine::dec_to_hex(uint16_t num)
{
	std::string res = "";

	while (num != 0)
	{
		res = (char)('a' + num % 16) + res;

		num /= 16;
	}

	return res;
}

uint16_t EnigmaMachine::hex_to_dec(std::string hex)
{
	uint16_t num = 0, mn = 0;
	for (int i = 0; i < hex.size(); ++i)
	{
		mn = hex[i] - 'a';

		num += pow(16, hex.size() - i - 1) * mn;
	}
	return num;
}

int16_t EnigmaMachine::GetCur(Rotors num)
{
	switch (num)
	{
	case EnigmaMachine::Rotors::FIRST:
		return this->cursors[0];

	case EnigmaMachine::Rotors::SECOND:
		return this->cursors[1];

	case EnigmaMachine::Rotors::THIRD:
		return this->cursors[2];

	default:
		return 0;
	}
}

char EnigmaMachine::Encode(char ch)
{
	if (ch < 'a' || ch >= '}')
		return '_';

	int tmp;

	if (this->commutations[ch - 'a'] != 0)
		ch = this->commutations[ch - 'a'];

	this->ShiftUp(Rotors::THIRD);

	int pos = 0;

	ch = (ch - 'a' + this->cursors[Rotors::THIRD]) % this->ROTOR_LEN + 'a';
	ch = this->rotors[Rotors::THIRD][ch - 'a'];
	ch = CycleSum(ch - 'a', this->cursors[Rotors::THIRD] * -1) + 'a';

	ch = (ch - 'a' + this->cursors[Rotors::SECOND]) % this->ROTOR_LEN + 'a';
	ch = this->rotors[Rotors::SECOND][ch - 'a'];
	ch = CycleSum(ch - 'a', this->cursors[Rotors::SECOND] * -1) + 'a';

	ch = (ch - 'a' + this->cursors[Rotors::FIRST]) % this->ROTOR_LEN + 'a';
	ch = this->rotors[Rotors::FIRST][ch - 'a'];
	ch = CycleSum(ch - 'a', this->cursors[Rotors::FIRST] * -1) + 'a';

	ch = this->reflector[ch - 'a'];

	ch = (ch - 'a' + this->cursors[Rotors::FIRST]) % this->ROTOR_LEN + 'a';
	pos = this->Find(this->rotors[Rotors::FIRST], ch);
	ch = CycleSum(pos, this->cursors[Rotors::FIRST] * -1) + 'a';

	ch = (ch - 'a' + this->cursors[Rotors::SECOND]) % this->ROTOR_LEN + 'a';
	pos = this->Find(this->rotors[Rotors::SECOND], ch);
	ch = CycleSum(pos, this->cursors[Rotors::SECOND] * -1) + 'a';

	ch = (ch - 'a' + this->cursors[Rotors::THIRD]) % this->ROTOR_LEN + 'a';
	pos = this->Find(this->rotors[Rotors::THIRD], ch);
	ch = CycleSum(pos, this->cursors[Rotors::THIRD] * -1) + 'a';

	if (this->commutations[ch - 'a'] != 0)
		ch = this->commutations[ch - 'a'];

	return ch;
}

char* EnigmaMachine::EncodeText(const char* text)
{
	if (!text)
		return nullptr;

	size_t len = strlen(text);

	if (!len)
		return nullptr;

	char* res = new char[len + 1];

	int i;
	for (i = 0; i < len; ++i)
		res[i] = this->Encode(text[i]);
	res[i] = '\0';

	return res;
}

sf::Color EnigmaMachine::EncodePixel(sf::Color pixel)
{
	sf::Color res;

	std::string rgb[3];

	if (pixel.r < 16)
	{
		rgb[0] = (int)'a' + pixel.r;
		rgb[0] = 'a' + rgb[0];
	}
	else
		rgb[0] = this->dec_to_hex(pixel.r);

	if (pixel.g < 16)
	{
		rgb[1] = (int)'a' + pixel.g;
		rgb[1] = 'a' + rgb[1];
	}
	else
		rgb[1] = this->dec_to_hex(pixel.g);

	if (pixel.b < 16)
	{
		rgb[2] = (int)'a' + pixel.b;
		rgb[2] = 'a' + rgb[2];
	}
	else
		rgb[2] = this->dec_to_hex(pixel.b);

	//std::cout << rgb[0] << ' ' << rgb[1] << ' ' << rgb[2] << '\n';

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < rgb[i].size(); ++j)
		{
			rgb[i][j] = this->Encode(rgb[i][j]);
		}
	}

	res = sf::Color(this->hex_to_dec(rgb[0]), this->hex_to_dec(rgb[1]), this->hex_to_dec(rgb[2]));
	return res;
}

void EnigmaMachine::ShiftUp(size_t rotor_num)
{
	bool flag = true;
	for (int i = rotor_num; i >= 0 && flag; --i)
	{
		flag = (this->rotors[i][this->ROTOR_LEN] - 'a') == cursors[i];

		if (cursors[i] + 1 == this->ROTOR_LEN)
			cursors[i] = 0;
		else
			cursors[i]++;
	}

	//std::cout << cursors[0] << ' ' << cursors[1] << ' ' << cursors[2] << '\n';
}

void EnigmaMachine::ShiftDown(size_t rotor_num)
{
	bool flag = true;
	for (int i = rotor_num; i >= 0 && flag; --i)
	{
		flag = (this->rotors[i][this->ROTOR_LEN] - 'a') == cursors[i];

		if (cursors[i] - 1 == -1)
			cursors[i] = (this->ROTOR_LEN - 1);
		else
			cursors[i]--;
	}

	//std::cout << cursors[0] << ' ' << cursors[1] << ' ' << cursors[2] << '\n';
}

void EnigmaMachine::SetReflector(const char* reflector)
{
	if (!reflector)
		return;

	this->Copy(this->reflector, reflector, this->ROTOR_LEN);
}

void EnigmaMachine::SetRotor(const char* rotor, Rotors num)
{
	if (!rotor || (num > 2))
		return;

	this->Copy(this->rotors[num], rotor, this->ROTOR_LEN + 1);
	this->Copy(this->initialRotors[num], rotor, this->ROTOR_LEN + 1);

	this->cursors[Rotors::FIRST]  = 0;
	this->cursors[Rotors::SECOND] = 0;
	this->cursors[Rotors::THIRD]  = 0;
}

void EnigmaMachine::SetSetting(Rotors num, uint16_t offset)
{
	if (offset >= this->ROTOR_LEN)
		return;

	for (int i = 0; i < this->ROTOR_LEN; ++i)
		this->rotors[num][i] = (this->initialRotors[num][i] + offset - 'a') % this->ROTOR_LEN + 'a';

	char* tmp = new char[this->ROTOR_LEN - offset];

	for (int i = 0; i < (this->ROTOR_LEN - offset); ++i)
		tmp[i] = this->rotors[num][i];

	int j = 0;
	for (int i = (this->ROTOR_LEN - offset); i < this->ROTOR_LEN; ++i, ++j)
		this->rotors[num][j] = this->rotors[num][i];

	for (int i = 0; j < this->ROTOR_LEN; ++j, ++i)
		this->rotors[num][j] = tmp[i];

	this->settings[num] = offset % this->ROTOR_LEN;

	//std::cout << rotors[num] << '\n';

	delete[] tmp;
}

void EnigmaMachine::SetCommutation(char source, char destination)
{
	if (source < 'a' || source > 'z' || destination < 'a' || destination > 'z')
		return;

	//std::cout << source << " " << destination << '\n';

	if (this->commutations[source - 'a'] != 0 || source == destination)
	{
		char tmp = this->commutations[source - 'a'];
		this->commutations[source - 'a'] = 0;
		this->commutations[tmp - 'a'] = 0;
	}
	else {
		this->commutations[source - 'a'] = destination;
		this->commutations[destination - 'a'] = source;
	}
}

char* EnigmaMachine::GetCommutations()
{
	return this->commutations;
}

char EnigmaMachine::GetRotorElem(Rotors rotor_num, int pos)
{

	if (pos >= 0)
	{
		pos %= this->ROTOR_LEN;

		if ((this->cursors[rotor_num] + pos) >= this->ROTOR_LEN)
		{
			pos = (this->cursors[rotor_num] + pos) - this->ROTOR_LEN;

			return (this->rotors[rotor_num][pos]);
		}
	}
	else
	{
		if ((this->cursors[rotor_num] + pos) < 0)
		{
			pos = this->ROTOR_LEN + (this->cursors[rotor_num] + pos);

			return (this->rotors[rotor_num][pos]);
		}
	}

	return (this->rotors[rotor_num][this->cursors[rotor_num] + pos]);
}

void EnigmaMachine::Copy(char* dest, const char* source, size_t nbytes)
{
	if (!dest || !source || !nbytes)
		return;

	for (int i = 0; i < nbytes; ++i)
		dest[i] = source[i];
}