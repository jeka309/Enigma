#pragma once

#include <SFML/Graphics.hpp>

#include <cstdint>

class EnigmaMachine {

	size_t ROTOR_LEN;
	size_t ROTORS_COUNT;

	char** initialRotors = nullptr;
	char** rotors = nullptr;
	char* reflector = nullptr;

	char* commutations = nullptr;

	int16_t* cursors = nullptr;

	void Copy(char* dest, const char* source, size_t nbytes);
	int Find(const char* rotor, char let);
	char CycleSum(char left, char right);

	std::string dec_to_hex(uint16_t num);
	uint16_t hex_to_dec(std::string hex);

public:

	uint16_t settings[3] = { 0, 0, 0 };

	enum Rotors {
		FIRST	= 0,
		SECOND	= 1,
		THIRD	= 2
	};

	EnigmaMachine(size_t rotor_len = 26, size_t rotors_count = 3);
	~EnigmaMachine();

	void ShiftUp(size_t rotor_num);
	void ShiftDown(size_t rotor_num);

	void SetRotor(const char* rotor, Rotors rotor_num);
	void SetReflector(const char* reflector);
	void SetSetting(Rotors num, uint16_t offset);
	void SetCommutation(char source, char destination);

	char* GetCommutations();

	int16_t GetCur(Rotors num);
	char GetRotorElem(Rotors rotor_num, int pos);

	char Encode(char ch);
	char* EncodeText(const char* text);
	sf::Color EncodePixel(sf::Color pixel);
};