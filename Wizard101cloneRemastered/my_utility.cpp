#include "my_utility.h"

#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77
#define ESCAPE_KEY 27

SpellsData spells;
std::unordered_map<int, Item> items;

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
	std::ifstream in;

	Spell temp_spell;
	in.open("Data/Spells/spells.txt");
	while (in.peek() != EOF) {
		in >> temp_spell;
		spells.spell[temp_spell.GetId()] = temp_spell;
	}
	in.close();

	in.open("Data/Spells/itemcards.txt");
	while (in.peek() != EOF) {
		in >> temp_spell;
		spells.ic[temp_spell.GetId()] = temp_spell;
	}
	in.close();

	in.open("Data/Spells/treasurecards.txt");
	while (in.peek() != EOF) {
		in >> temp_spell;
		spells.tc[temp_spell.GetId()] = temp_spell;
	}
	in.close();

	Item temp_item;
	in.open("Data/items.txt");
	while (in.peek() != EOF) {
		in >> temp_item;
		items[temp_item.GetId()] = temp_item;
	}
	in.close();
}
void LoadLevel(const locations_enum& location) {
	std::ifstream in;

	// convert enum to wstring
	std::wstring wstr;
	for (const auto& n : map_wstr_location) {
		if (location == n.second) {
			wstr = n.first;
			break;
		}
	}

	in.open("Data/Levels/" + narrow(wstr) + ".txt");
	in >> current_level;
	in.close();
}

// ----- game functionality -----
void Gameloop() {
	char choice;
	while (true) {
		system("CLS");
		current_level.DrawLevel();
		choice = _getch();
		switch (choice) {
			case 'w':
			case ARROW_UP:
				// move up
				MovePlayer(0, -1);
				break;
			case 's':
			case ARROW_DOWN:
				// move down
				MovePlayer(0, 1);
				break;
			case 'a':
			case ARROW_LEFT:
				// move left
				MovePlayer(-1, 0);
				break;
			case 'd':
			case ARROW_RIGHT:
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
				SpellDeckMenu();
				break;
			case 'q':
				// open quests tab
				break;
			case ESCAPE_KEY:
				// open options menu
				exit(0);
				break;
		}
	}
}
void MovePlayer(int x, int y) {
	Position previous_pos = player.GetPosition();
	Enemy* enemy_ptr;
	Gateway* gateway_ptr;
	Npc* npc_ptr;
	switch (current_level.GetCell(previous_pos + Position(x, y)).cell_type) {
		case cell_type_enum::Empty:
			player.SetPosition(previous_pos + Position(x, y));
			current_level.SpawnEntity(&player);
			current_level.ClearCell(previous_pos);
			break;
		case cell_type_enum::Enemy:
			// start battle with enemy
			enemy_ptr = static_cast<Enemy*>(current_level.GetCell(previous_pos + Position(x, y)).entity_ptr);
			// if player won, erase enemy
			// else teleport player to default spawn in current world
			break;
		case cell_type_enum::Gateway:
			// teleport to gateway's destination
			gateway_ptr = static_cast<Gateway*>(current_level.GetCell(previous_pos + Position(x, y)).entity_ptr);
			current_level.ClearLevel();
			player.SetPosition(gateway_ptr->GetDestinationSpawnPos());
			LoadLevel(gateway_ptr->GetDestination());
			current_level.SpawnEntity(&player);
			break;
		case cell_type_enum::Npc:
			// talk to npc
			npc_ptr = static_cast<Npc*>(current_level.GetCell(previous_pos + Position(x, y)).entity_ptr);
			break;
	}
}
void SpellDeckMenu() {
	int page[5] = { 1,1,1,1,1 }; // deck, unlocked spells, equipped tc, owned tc, ic
	int max_page[5];
	char choice;
	bool loop = true;
	auto current_menu = spell_deck_menu_enum::Deck;
	while (loop) {
		auto& deck = player.GetDeckRef();
		auto unlocked_spells = player.GetUnlockedSpells();
		auto& eq_tc = deck.treasure_cards;
		auto owned_tc = player.GetTreasureCards(); // doesn't include eq_tc
		auto owned_ic = player.GetItemCards();

		max_page[0] = deck.spells.size() > 0 ? (deck.spells.size() - 1) / 5 + 1 : 1;
		max_page[1] = unlocked_spells.size() > 0 ? (unlocked_spells.size() - 1) / 5 + 1 : 1;
		max_page[2] = eq_tc.size() > 0 ? (eq_tc.size() - 1) / 5 + 1 : 1;
		max_page[3] = owned_tc.size() > 0 ? (owned_tc.size() - 1) / 5 + 1 : 1;
		max_page[4] = owned_ic.size() > 0 ? (owned_ic.size() - 1) / 5 + 1 : 1;
		// Your deck:
		//	<equipped spells' stats + amount equipped / max (max is determined by equipped deck item)>
		// Your spells:
		//	<unlocked spells' stats>
		// Your equipped treasure cards:
		//	<equipped treasure cards' stats>
		// Your treasure cards:
		//	<treasure cards' stats>
		// Your item cards:
		//	<item cards' stats>

		system("CLS");
		// deck
		std::wcout << "Your deck: \n";
		for (int i = 0; i < 5; i++) {
			if ((page[0] - 1) * 5 + i < deck.spells.size()) {
				auto spell = spells.spell[deck.spells[(page[0] - 1) * 5 + i]];
				// Fire cat    Cost: 1    School: Fire    Accuracy: 75    80-120 Fire damage
				std::wcout << spell.GetName() << "    Cost: " << spell.GetCost() << "    School: ";
				for (const auto& n : map_wstr_school) {
					if (school_enum(spell.GetSchool()) == n.second) {
						std::wcout << n.first;
						break;
					}
				}
				std::wcout << "    Accuracy: " << spell.GetAccuracy() << "    " << spell.GetDescripition() << std::endl;
			}
		}
		// <<   Page: 2/3   >>
		if (page[0] != 1)
			std::wcout << "<<  ";
		else std::wcout << "    ";
		if (current_menu == spell_deck_menu_enum::Deck)
			std::wcout << ">Page: " << page[0] << " / " << max_page[0];
		else std::wcout << " Page: " << page[0] << " / " << max_page[0];
		if (page[0] != max_page[0])
			std::wcout << "   >>";


		//  unlocked spells
		std::wcout << "\n\n\nYour spells: \n";
		for (int i = 0; i < 5; i++) {
			if ((page[1] - 1) * 5 + i < unlocked_spells.size()) {
				
				auto spell = spells.spell[unlocked_spells[(page[1] - 1) * 5 + i]];
				// Fire cat    Cost: 1    School: Fire    Accuracy: 75    80-120 Fire damage
				std::wcout << spell.GetName() << "    Cost: " << spell.GetCost() << "    School: ";
				for (const auto& n : map_wstr_school) {
					if (school_enum(spell.GetSchool()) == n.second) {
						std::wcout << n.first;
						break;
					}
				}
				std::wcout << "    Accuracy: " << spell.GetAccuracy() << "    " << spell.GetDescripition() << std::endl;
			}
		}
		// <<   Page: 2/3   >>
		if (page[1] != 1)
			std::wcout << "<<  ";
		else std::wcout << "    ";
		if (current_menu == spell_deck_menu_enum::Unlocked_Spells)
			std::wcout << ">Page: " << page[1] << " / " << max_page[1];
		else std::wcout << " Page: " << page[1] << " / " << max_page[1];
		if (page[1] != max_page[1])
			std::wcout << "   >>";


		// equipped treasure cards
		std::wcout << "\n\n\nYour equipped treasure cards: \n";
		for (int i = 0; i < 5; i++) {
			if ((page[2] - 1) * 5 + i < eq_tc.size()) {

				auto spell = spells.tc[eq_tc[(page[2] - 1) * 5 + i]];
				// Fire cat    Cost: 1    School: Fire    Accuracy: 75    80-120 Fire damage
				std::wcout << spell.GetName() << "    Cost: " << spell.GetCost() << "    School: ";
				for (const auto& n : map_wstr_school) {
					if (school_enum(spell.GetSchool()) == n.second) {
						std::wcout << n.first;
						break;
					}
				}
				std::wcout << "    Accuracy: " << spell.GetAccuracy() << "    " << spell.GetDescripition() << std::endl;
			}
		}
		// <<   Page: 2/3   >>
		if (page[2] != 1)
			std::wcout << "<<  ";
		else std::wcout << "    ";
		if (current_menu == spell_deck_menu_enum::Equipped_Treasure_Cards)
			std::wcout << ">Page: " << page[2] << " / " << max_page[2];
		else std::wcout << " Page: " << page[2] << " / " << max_page[2];
		if (page[2] != max_page[2])
			std::wcout << "   >>";


		// owned treasure cards
		std::wcout << "\n\n\nYour treasure cards: \n";
		for (int i = 0; i < 5; i++) {
			if ((page[3] - 1) * 5 + i < owned_tc.size()) {

				auto spell = spells.tc[owned_tc[(page[3] - 1) * 5 + i]];
				// Fire cat    Cost: 1    School: Fire    Accuracy: 75    80-120 Fire damage
				std::wcout << spell.GetName() << "    Cost: " << spell.GetCost() << "    School: ";
				for (const auto& n : map_wstr_school) {
					if (school_enum(spell.GetSchool()) == n.second) {
						std::wcout << n.first;
						break;
					}
				}
				std::wcout << "    Accuracy: " << spell.GetAccuracy() << "    " << spell.GetDescripition() << std::endl;
			}
		}
		// <<   Page: 2/3   >>
		if (page[3] != 1)
			std::wcout << "<<  ";
		else std::wcout << "    ";
		if (current_menu == spell_deck_menu_enum::Treasure_Cards)
			std::wcout << ">Page: " << page[3] << " / " << max_page[3];
		else std::wcout << " Page: " << page[3] << " / " << max_page[3];
		if (page[3] != max_page[3])
			std::wcout << "   >>";


		// owned item cards
		std::wcout << "\n\n\nYour item cards: \n";
		for (int i = 0; i < 5; i++) {
			if ((page[4] - 1) * 5 + i < owned_ic.size()) {

				auto spell = spells.ic[owned_ic[(page[4] - 1) * 5 + i]];
				// Fire cat    Cost: 1    School: Fire    Accuracy: 75    80-120 Fire damage
				std::wcout << spell.GetName() << "    Cost: " << spell.GetCost() << "    School: ";
				for (const auto& n : map_wstr_school) {
					if (school_enum(spell.GetSchool()) == n.second) {
						std::wcout << n.first;
						break;
					}
				}
				std::wcout << "    Accuracy: " << spell.GetAccuracy() << "    " << spell.GetDescripition() << std::endl;
			}
		}
		// <<   Page: 2/3   >>
		if (page[4] != 1)
			std::wcout << "<<  ";
		else std::wcout << "    ";
		if (current_menu == spell_deck_menu_enum::Item_Cards)
			std::wcout << ">Page: " << page[4] << " / " << max_page[4];
		else std::wcout << " Page: " << page[4] << " / " << max_page[4];
		if (page[4] != max_page[4])
			std::wcout << "   >>";

		choice = _getch();
		switch (choice) {
			case 'w':
			case ARROW_UP:
				// change to previous menu
				if (current_menu != spell_deck_menu_enum::Deck)
					current_menu = spell_deck_menu_enum(int(current_menu) - 1);
				break;
			case 's':
			case ARROW_DOWN:
				// change to next menu
				if (current_menu != spell_deck_menu_enum::Item_Cards)
					current_menu = spell_deck_menu_enum(int(current_menu) + 1);
				break;
			case 'a':
			case ARROW_LEFT:
				if (page[int(current_menu) - 1] != 1)
					page[int(current_menu) - 1]--;
				break;
			case 'd':
			case ARROW_RIGHT:
				if (page[int(current_menu) - 1] != max_page[int(current_menu) - 1])
					page[int(current_menu) - 1]++;
				break;
			case 'p':
			case ESCAPE_KEY:
				loop = false;
				break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
				switch (current_menu) {
				case spell_deck_menu_enum::Deck:
					if (choice - '1' + (page[0] - 1) * 5 < deck.spells.size())
						player.UnequipSpell(deck.spells[choice - '1' + (page[0] - 1) * 5]);
					break;
				case spell_deck_menu_enum::Unlocked_Spells:
					if (choice - '1' + (page[1] - 1) * 5 < unlocked_spells.size())
						player.EquipSpell(unlocked_spells[choice - '1' + (page[1] - 1) * 5]);
					break;
				case spell_deck_menu_enum::Equipped_Treasure_Cards:
					if (choice - '1' + (page[2] - 1) * 5 < player.GetEquippedTreasureCards().size())
						player.UnequipTreasureCard(player.GetEquippedTreasureCards()[choice - '1' + (page[2] - 1) * 5]);
					break;
				case spell_deck_menu_enum::Treasure_Cards:
					if (choice - '1' + (page[3] - 1) * 5 < player.GetTreasureCards().size())
						player.EquipTreasureCard(player.GetTreasureCards()[choice - '1' + (page[3] - 1) * 5]);
					break;
				case spell_deck_menu_enum::Item_Cards:
					break;
				}
				break;
		}
	}
}