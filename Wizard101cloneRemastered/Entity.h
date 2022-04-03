#pragma once
#include "my_globals.h"

#include <iostream>

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
	void SetAppearance(wchar_t appearance);
	
	// ----- data -----
protected:
	Position m_pos;
	wchar_t m_appearance;
};

