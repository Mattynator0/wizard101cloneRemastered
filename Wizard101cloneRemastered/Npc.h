#pragma once
#include "Entity.h"

#include <iostream>
#include <string>

const int n_npcs = 0;

class Npc :
    public Entity
{
	// ----- functions -----
public:
	Npc(char appearance, std::string name);

	// <-- encapsulation -->
	std::string GetName();
	char GetAppearance();

	// ----- data -----
private:
	char m_appearance;
	std::string m_name;

};
