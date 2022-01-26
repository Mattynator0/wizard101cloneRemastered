#pragma once
#include "Entity.h"

#include <array>
#include <vector>

struct LevelCap;

class Player : public Entity
{
// ----- functions -----
public:
	Player(const std::wstring& name);

	// <-- encapsulation -->
	std::wstring& GetName();
	int GetLevel();
	int GetExp();
	void AddExp(int n);
	std::vector<int> GetUnlockedSpells();
	std::vector<int> GetSpellsInDeck();
	
	Player(Player&) = delete;
	void operator=(const Player&) = delete;

// ----- data -----
protected:
	std::wstring m_name;
	int m_level = 1, m_exp = 0;

	std::vector<int> m_unlocked_spells = { 1 };
	std::vector<int> m_spells_in_deck;
};

extern Player player;