#include "my_utility.h"

Level current_level;
Player player("Mattynator");

std::array<Spell, n_spells> spells;
std::array<Item, n_items> items;
std::array<Enemy, n_enemies> enemies;

void LoadData() {
	std::ifstream ifile;

	ifile.open("Data/spells.txt");
	for (int i = 0; i < n_spells; i++) {
		ifile >> spells[i];
	}
	ifile.close();

	ifile.open("Data/items.txt");
	for (int i = 0; i < n_items; i++) {
		ifile >> items[i];
	}
	ifile.close();
#if 1
	ifile.open("Data/enemies.txt");
	for (int i = 0; i < n_enemies; i++) {
		ifile >> enemies[i];
	}
	ifile.close();
#endif
}

void LoadLevel(const locations_enum& location) {
	std::ifstream ifile;

	std::string str;
	for (const auto& n : map_string_to_location) {
		if (location == n.second) {
			str = n.first;
			break;
		}
	}
	
	ifile.open("Data/Levels/" + str + ".txt");
	bool good = ifile.good();
	ifile >> current_level;
	ifile.close();
}

void Gameloop() {
	while (true) {
		system("CLS");
		current_level.DrawLevel();
		std::cin.get();
	}
}