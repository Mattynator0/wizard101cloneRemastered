#pragma once
#include "Item.h"
#include "Level.h"
#include "Spell.h"

#include <array>
#include <conio.h>
#include <codecvt>
#include <fcntl.h>
#include <fstream>
#include <io.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

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

extern SpellArray spells;
extern ItemArray items;
extern std::array<Enemy, n_enemies> enemies;

// ----- entities in current level -----
extern std::vector<Npc> spawned_npcs;
extern std::vector<Gateway> spawned_gateways;
extern std::vector<Enemy> spawned_enemies;

void ShowConsoleCursor(bool showFlag);

// ----- loading stuff from files -----
void LoadData();
void LoadLevel(const locations_enum& location);

// ----- game functionality -----
void Gameloop();
void MovePlayer(int x, int y);
void SpellDeckMenu();