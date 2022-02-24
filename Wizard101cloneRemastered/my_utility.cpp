#include "my_utility.h"

SpellArray spells;
ItemArray items;
std::array<Enemy, n_enemies> enemies;

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

// ----- loading stuff from files -----
void LoadData() {
	std::ifstream ifile;

	ifile.open("Data/spells.txt");
	for (int i = 0; i < n_spells; i++) {
		ifile >> spells.arr[i];
	}
	ifile.close();

	ifile.open("Data/items.txt");
	for (int i = 0; i < n_items; i++) {
		ifile >> items.arr[i];
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
	std::wstring wstr;
	for (const auto& n : map_wstring_to_location) {
		if (location == n.second) {
			wstr = n.first;
			break;
		}
	}
	// convert wstring to string
	std::string str = narrow(wstr);

	ifile.open("Data/Levels/" + str + ".txt");
	ifile >> current_level;
	ifile.close();
}

// ----- game functionality -----
void Gameloop() {
	while (true) {
		system("CLS");
		current_level.DrawLevel();
		wchar_t choice;
		choice = _getch();
		switch (choice) {
			case 'w':
				// move up
				MovePlayer(0, -1);
				break;
			case 's':
				// move down
				MovePlayer(0, 1);
				break;
			case 'a':
				// move left
				MovePlayer(-1, 0);
				break;
			case 'd':
				// move right
				MovePlayer(1, 0);
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
				DrawSpellDeckUI();
				break;
			case 'q':
				// open quests tab
				break;
			default:
				continue;

		}
	}
}
void MovePlayer(int x, int y) {
	Position saved_pos = player.GetPosition();
	Gateway* gateway_ptr;
	switch (current_level.GetCell({ saved_pos.x + x, saved_pos.y + y }).cell_type) {
		case cell_type_enum::Empty:
			player.SetPosition({ saved_pos.x + x, saved_pos.y + y });
			current_level.SpawnEntity(&player);
			current_level.ClearCell(saved_pos);
			break;
		case cell_type_enum::Enemy:
			// start battle
			// if player won, erase enemy
			// else teleport player to default spawn in The Commons
			break;
		case cell_type_enum::Gateway:
			// teleport to gateway's destination
			gateway_ptr = dynamic_cast<Gateway*>(current_level.GetCell({ saved_pos.x + x, saved_pos.y + y }).entity_ptr);
			current_level.ClearLevel();
			player.SetPosition(gateway_ptr->GetDestinationSpawnPos());
			LoadLevel(gateway_ptr->GetDestination());
			current_level.SpawnEntity(&player);
			break;
		case cell_type_enum::Npc:
			// talk to npc
			break;
	}
}
void DrawSpellDeckUI() {
	int deck_page = 1;
	char choice;
	while (true) {
		// Your deck:
		// <equipped spells' stats + amount equipped / max (max determined by equipped deck item)>
		// Your spells:
		// 
		system("CLS");
		std::wcout << "Your deck: \n";
		std::vector<int> deck = player.GetUnlockedSpells();
		Spell temp_spell;
		for (int i = 0; i < 5; i++) {
			if (i >= deck.size())
				break;
			temp_spell = spells[deck[i]];
			std::wcout << temp_spell.GetName() << " | cost: " << temp_spell.GetCost() << /*" | school: " << temp_spell.GetSchool() <<*/ " | accuracy: " // TODO: display school as text (prob using an unordered_map
					<< temp_spell.GetAccuracy() << "% | " << temp_spell.GetDescripition() << "\n";
		}
		choice = _getch();
	}
}