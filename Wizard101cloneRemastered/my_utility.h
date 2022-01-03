#pragma once
#include "Enemy.h"
#include "Item.h"
#include "Level.h"
#include "Npc.h"
#include "Player.h"
#include "Spell.h"

#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#ifdef _DEBUG
#include <cassert> // assertion
#endif

template<typename _T>
void GetInput(_T& input, _T* valid_inputs, int n_valid_inputs) {
	while (true) {
		// if cin raises a flag, repeat
		if (!(std::cin >> input)) {
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		// else if input is not one of the specified, repeat
		else {
			for (int i = 0; i < n_valid_inputs; i++) {
				if (input = *(valid_inputs + i))
					break;
			}
		}
	}
}

extern Level current_level;
extern Player player;

extern std::array<Spell, n_spells> spells;
extern std::array<Item, n_items> items;
extern std::array<Enemy, n_enemies> enemies;

// ----- entities in current level -----
extern std::vector<Npc> spawned_npcs;
extern std::vector<Gateway> spawned_gateways;
extern std::vector<Enemy> spawned_enemies;

// ----- loading stuff from files -----
void LoadData();

void LoadLevel(const locations_enum& location);

void Gameloop();