#pragma once
#include "Item.h"
#include "Level.h"
#include "Spell.h"

#include <conio.h>
#include <codecvt>
#include <fcntl.h>
#include <fstream>
#include <io.h>
#include <iostream>
#include <map>
#include <random>
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
template<typename _T>
_T RNG(_T lower, _T upper) {
	std::random_device rand_dev; // obtain a random number from hardware
	std::mt19937 generator(rand_dev()); // seed the generator
	std::uniform_int_distribution<_T> distr(lower, upper); // define the range
	return distr(generator);
}

extern SpellsData spells;
extern std::unordered_map<int, Item> items;

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
void BeginBattle(Enemy* enemy_ptr);
void SpellDeckMenu();