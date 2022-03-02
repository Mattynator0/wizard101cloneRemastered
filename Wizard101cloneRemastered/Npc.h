#pragma once
#include "Entity.h"

#include <iostream>

const int n_npcs = 0;

class Npc :
    public Entity
{
	// ----- functions -----
public:
	Npc(wchar_t appearance, std::wstring name);

	// <-- encapsulation -->
	std::wstring GetName() const;
	wchar_t GetAppearance() const;

	// ----- data -----
private:
	wchar_t m_appearance;
	std::wstring m_name;

};
