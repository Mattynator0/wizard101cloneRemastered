#include "my_utility.h"

std::array<Spell, n_spells> spells;
std::array<Item, n_items> items;
std::array<Enemy, n_enemies> enemies;

// ----- loading stuff from files -----
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

	ifile.open("Data/enemies.txt");
	for (int i = 0; i < n_enemies; i++) {
		ifile >> enemies[i];
	}
	ifile.close();
}
void LoadLevel(const locations_enum& location) {
	std::ifstream ifile;

	// convert enum to string
	std::string str;
	for (const auto& n : map_string_to_location) {
		if (location == n.second) {
			str = n.first;
			break;
		}
	}
	
	ifile.open("Data/Levels/" + str + ".txt");
	ifile >> current_level;
	ifile.close();
}

// ----- game functionality -----
void Gameloop() {
	while (true) {
		system("CLS");
		current_level.DrawLevel();
		char choice;
		while (true) {
			choice = _getch();
			switch (choice) {
				case 'w':
					// move up
					MovePlayer(0, -1);
					goto exit_second_while;
					break;
				case 's':
					// move down
					MovePlayer(0, 1);
					goto exit_second_while;
					break;
				case 'a':
					// move left
					MovePlayer(-1, 0);
					goto exit_second_while;
					break;
				case 'd':
					// move right
					MovePlayer(1, 0);
					goto exit_second_while;
					break;
				case 'x':
					// interact
					break;
				case 'c':
					// open charachter tab
					break;
				case 'b':
					// open backpack
					break;
				case 'p':
					// open spell deck
					break;
				case 'q':
					// open quests tab
					break;
				default:
					continue;

			}
		}
		exit_second_while:;
	}
}
void MovePlayer(int x, int y) {
	Position saved_pos = player.GetPosition();
	switch (current_level.GetCell({ saved_pos.x + x, saved_pos.y + y }).cell_type) {
		case cell_type_enum::Empty:
			player.SetPosition({ saved_pos.x + x, saved_pos.y + y });
			current_level.SpawnEntity(&player);
			current_level.ClearCell(saved_pos);
			break;
		case cell_type_enum::Enemy:
			// start battle
			// if player won, erase enemy
			// else teleport player to default spawn in The_Commons
			break;
		case cell_type_enum::Gateway:
			// teleport to gateway's destination
			break;
		case cell_type_enum::Npc:
			// talk to npc
			break;
	}
}