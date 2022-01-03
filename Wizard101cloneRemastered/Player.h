#pragma once
#include "Entity.h"

#include <array>
#include <string>

struct LevelCap;

class Player : public Entity
{
// ----- functions -----
public:
	Player(const std::string& name);

	// <-- encapsulation -->
	std::string& GetName();
	int GetLevel();
	int GetExp();
	void AddExp(int n);
	

	Player(Player&) = delete;
	void operator=(const Player&) = delete;

// ----- data -----
protected:
	std::string m_name;
	int m_level = 1, m_exp = 0;

};