#pragma once
#include "my_globals.h"

struct Position {
	int x, y;
};

class Entity
{
	// ----- functions -----
public:

	// <-- encapsulation -->
	Position Get_position() const;
	void Set_position(Position position);
	virtual char Get_appearance() const;
	void Set_appearance(char appearance);
	
	// ----- data -----
protected:
	Position m_pos;
	char m_appearance;
};

