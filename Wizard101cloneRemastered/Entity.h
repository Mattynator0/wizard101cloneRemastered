#pragma once
#include "my_globals.h"

#include <iostream>
#include <random>

struct Position {
	Position();
	Position(int x, int y);

	int to_index(Position size) const;
	Position operator+(Position other);
	
	int x, y;
};
std::istream& operator>> (std::istream& in, Position& position);

class Entity
{
	// ----- functions -----
public:

	// <-- encapsulation -->
	Position GetPosition() const;
	void SetPosition(Position position);
	virtual wchar_t GetAppearance() const;
	void SetAppearance(char app);
	
	// ----- data -----
protected:
	Position m_pos = { -1, -1 };
	wchar_t m_appearance = ' ';
};

