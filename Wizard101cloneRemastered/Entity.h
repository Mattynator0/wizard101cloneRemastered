#pragma once
#include "my_globals.h"

#include <iostream>

struct Position {
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
	virtual char GetAppearance() const;
	void SetAppearance(char appearance);
	
	// ----- data -----
protected:
	Position m_pos;
	char m_appearance;
};

