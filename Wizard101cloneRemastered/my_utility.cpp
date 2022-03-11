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

// ----- loading stuff in from files -----
void LoadData() {
	std::ifstream ifile;

	ifile.open("Data/Spells/spells.txt");
	for (int i = 0; i < n_spells[0]; i++) {
		ifile >> spells.spells[i];
	}
	ifile.close();

	ifile.open("Data/Spells/itemcards.txt");
	for (int i = 0; i < n_spells[1]; i++) {
		ifile >> spells.item_cards[i];
	}
	ifile.close();

	ifile.open("Data/Spells/treasurecards.txt");
	for (int i = 0; i < n_spells[2]; i++) {
		ifile >> spells.treasure_cards[i];
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
				SpellDeck();
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
void SpellDeck() {
	int deck_page = 1, spells_page = 1;
	Deck deck = player.GetDeck();
	auto unlocked_spells = player.GetUnlockedSpells();
	char choice;
	bool loop = true;
	while (loop) {
		// Your deck:
		// <equipped spells' stats + amount equipped / max (max determined by equipped deck item)>
		// Your spells:
		// 
		system("CLS");
		std::wcout << "Your deck: \n";
		for (int i = 0; i < 5; i++) {
			if ((deck_page - 1) * 5 + i < deck.spells.size()) {
				auto spell = spells(deck.spells[(deck_page - 1) * 5 + i], card_type_enum::Spell);
				// Fire cat    Cost: 1    School: Fire    Accuracy: 75    80-120 Fire damage
				std::wcout << spell.GetName() << "    Cost: " << spell.GetCost() << "    School: ";
				for (const auto& n : map_wstring_to_location) {
					if (school_enum(spell.GetSchool()) == school_enum(n.second)) {
						std::wcout << n.first;
						break;
					}
				}
				std::wcout << "    Accuracy: " << spell.GetAccuracy() << "    " << spell.GetDescripition() << std::endl;
			}
		}
		// <<   Page: 2/3   >>
		if (deck_page != 1)
			std::wcout << "<<   ";
		else std::wcout << "     ";
		int max_deck_page = deck.spells.size() / 5 + 1;
		std::wcout << "Page: " << deck_page << " / " << max_deck_page;
		if (deck_page != max_deck_page)
			std::wcout << "   >>";

		std::wcout << "\n\nYour spells: \n";
		for (int i = 0; i < 5; i++) {
			if ((spells_page - 1) * 5 + i < unlocked_spells.size()) {
				auto spell = spells(deck.spells[(deck_page - 1) * 5 + i], card_type_enum::Spell);
				// Fire cat    Cost: 1    School: Fire    Accuracy: 75    80-120 Fire damage
				std::wcout << spell.GetName() << "    Cost: " << spell.GetCost() << "    School: ";
				for (const auto& n : map_wstring_to_location) {
					if (school_enum(spell.GetSchool()) == school_enum(n.second)) {
						std::wcout << n.first;
						break;
					}
				}
				std::wcout << "    Accuracy: " << spell.GetAccuracy() << "    " << spell.GetDescripition() << std::endl;
			}
		}
		// <<   Page: 2/3   >>
		if (deck_page != 1)
			std::wcout << "<<   ";
		else std::wcout << "     ";
		int max_deck_page = deck.spells.size() / 5 + 1;
		std::wcout << "Page: " << deck_page << " / " << max_deck_page;
		if (deck_page != max_deck_page)
			std::wcout << "   >>";
		choice = _getch();
		switch (choice) {
			case 75: // left arrow
				if (deck_page != 1)
					deck_page--;
				break;
			case 77: // right arrow
				if (deck_page != max_page)
					deck_page++;
				break;
			case 27: // Esc
				loop = false;
				break;
			case 'p':
				loop = false;
				break;
		}
	}
}