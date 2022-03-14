#include "my_utility.h"

#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77
#define ESCAPE_KEY 27

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
				break;
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
void SpellDeckMenu() {
	int deck_page = 1, spells_page = 1, tc_page = 1, eq_tc_page = 1, ic_page = 1;
	char choice;
	bool loop = true;
	auto spell_deck_menu = spell_deck_menu_enum::Deck;
	while (loop) {
		auto& deck = player.GetDeckRef(); // this solution is kinda ugly, but I couldn't find a better way to get a reference to player.m_deck
		auto unlocked_spells = player.GetUnlockedSpells();
		auto& eq_tc = deck.treasure_cards;
		auto owned_tc = player.GetTreasureCards();
		auto owned_ic = player.GetItemCards();
		// Your deck:
		// <equipped spells' stats + amount equipped / max (max is determined by equipped deck item)>
		// Your spells:
		// <unlocked spells' stats>
		// Your equipped treasure cards:
		// <equipped treasure cards' stats>
		// Your treasure cards:
		// <treasure cards' stats>
		// Your item cards:
		// <item cards' stats>
		system("CLS");

		// deck
		std::wcout << "Your deck: \n";
		for (int i = 0; i < 5; i++) {
			if ((deck_page - 1) * 5 + i < deck.spells.size()) {
				auto spell = spells(deck.spells[(deck_page - 1) * 5 + i], card_type_enum::Spell);
				// Fire cat    Cost: 1    School: Fire    Accuracy: 75    80-120 Fire damage
				std::wcout << spell.GetName() << "    Cost: " << spell.GetCost() << "    School: ";
				for (const auto& n : map_wstring_to_school) {
					if (school_enum(spell.GetSchool()) == n.second) {
						std::wcout << n.first;
						break;
					}
				}
				std::wcout << "    Accuracy: " << spell.GetAccuracy() << "    " << spell.GetDescripition() << std::endl;
			}
		}
		// <<   Page: 2/3   >>
		if (deck_page != 1)
			std::wcout << "<<  ";
		else std::wcout << "    ";
		int max_deck_page = deck.spells.size() > 0 ? (deck.spells.size() - 1) / 5 + 1 : 1;
		if (spell_deck_menu == spell_deck_menu_enum::Deck)
			std::wcout << ">Page: " << deck_page << " / " << max_deck_page;
		else std::wcout << " Page: " << deck_page << " / " << max_deck_page;
		if (deck_page != max_deck_page)
			std::wcout << "   >>";


		//  unlocked spells
		std::wcout << "\n\n\nYour spells: \n";
		for (int i = 0; i < 5; i++) {
			if ((spells_page - 1) * 5 + i < unlocked_spells.size()) {
				
				auto spell = spells(unlocked_spells[(spells_page - 1) * 5 + i], card_type_enum::Spell);
				// Fire cat    Cost: 1    School: Fire    Accuracy: 75    80-120 Fire damage
				std::wcout << spell.GetName() << "    Cost: " << spell.GetCost() << "    School: ";
				for (const auto& n : map_wstring_to_school) {
					if (school_enum(spell.GetSchool()) == n.second) {
						std::wcout << n.first;
						break;
					}
				}
				std::wcout << "    Accuracy: " << spell.GetAccuracy() << "    " << spell.GetDescripition() << std::endl;
			}
		}
		// <<   Page: 2/3   >>
		if (spells_page != 1)
			std::wcout << "<<  ";
		else std::wcout << "    ";
		int max_spells_page = unlocked_spells.size() > 0 ? (unlocked_spells.size() - 1) / 5 + 1 : 1;
		if (spell_deck_menu == spell_deck_menu_enum::Unlocked_Spells)
			std::wcout << ">Page: " << spells_page << " / " << max_spells_page;
		else std::wcout << " Page: " << spells_page << " / " << max_spells_page;
		if (spells_page != max_spells_page)
			std::wcout << "   >>";


		// equipped treasure cards
		std::wcout << "\n\n\nYour equipped treasure cards: \n";
		for (int i = 0; i < 5; i++) {
			if ((eq_tc_page - 1) * 5 + i < eq_tc.size()) {

				auto spell = spells(eq_tc[(eq_tc_page - 1) * 5 + i], card_type_enum::Treasure_Card);
				// Fire cat    Cost: 1    School: Fire    Accuracy: 75    80-120 Fire damage
				std::wcout << spell.GetName() << "    Cost: " << spell.GetCost() << "    School: ";
				for (const auto& n : map_wstring_to_school) {
					if (school_enum(spell.GetSchool()) == n.second) {
						std::wcout << n.first;
						break;
					}
				}
				std::wcout << "    Accuracy: " << spell.GetAccuracy() << "    " << spell.GetDescripition() << std::endl;
			}
		}
		// <<   Page: 2/3   >>
		if (eq_tc_page != 1)
			std::wcout << "<<  ";
		else std::wcout << "    ";
		int max_eq_tc_page = eq_tc.size() > 0 ? (eq_tc.size() - 1) / 5 + 1 : 1;
		if (spell_deck_menu == spell_deck_menu_enum::Equipped_Treasure_Cards)
			std::wcout << ">Page: " << eq_tc_page << " / " << max_eq_tc_page;
		else std::wcout << " Page: " << eq_tc_page << " / " << max_eq_tc_page;
		if (eq_tc_page != max_eq_tc_page)
			std::wcout << "   >>";


		// owned treasure cards
		std::wcout << "\n\n\nYour treasure cards: \n";
		for (int i = 0; i < 5; i++) {
			if ((tc_page - 1) * 5 + i < owned_tc.size()) {

				auto spell = spells(owned_tc[(tc_page - 1) * 5 + i], card_type_enum::Treasure_Card);
				// Fire cat    Cost: 1    School: Fire    Accuracy: 75    80-120 Fire damage
				std::wcout << spell.GetName() << "    Cost: " << spell.GetCost() << "    School: ";
				for (const auto& n : map_wstring_to_school) {
					if (school_enum(spell.GetSchool()) == n.second) {
						std::wcout << n.first;
						break;
					}
				}
				std::wcout << "    Accuracy: " << spell.GetAccuracy() << "    " << spell.GetDescripition() << std::endl;
			}
		}
		// <<   Page: 2/3   >>
		if (tc_page != 1)
			std::wcout << "<<  ";
		else std::wcout << "    ";
		int max_tc_page = owned_tc.size() > 0 ? (owned_tc.size() - 1) / 5 + 1 : 1;
		if (spell_deck_menu == spell_deck_menu_enum::Treasure_Cards)
			std::wcout << ">Page: " << tc_page << " / " << max_tc_page;
		else std::wcout << " Page: " << tc_page << " / " << max_tc_page;
		if (tc_page != max_tc_page)
			std::wcout << "   >>";


		// owned item cards
		std::wcout << "\n\n\nYour item cards: \n";
		for (int i = 0; i < 5; i++) {
			if ((ic_page - 1) * 5 + i < owned_ic.size()) {

				auto spell = spells(owned_ic[(ic_page - 1) * 5 + i], card_type_enum::Item_Card);
				// Fire cat    Cost: 1    School: Fire    Accuracy: 75    80-120 Fire damage
				std::wcout << spell.GetName() << "    Cost: " << spell.GetCost() << "    School: ";
				for (const auto& n : map_wstring_to_school) {
					if (school_enum(spell.GetSchool()) == n.second) {
						std::wcout << n.first;
						break;
					}
				}
				std::wcout << "    Accuracy: " << spell.GetAccuracy() << "    " << spell.GetDescripition() << std::endl;
			}
		}
		// <<   Page: 2/3   >>
		if (ic_page != 1)
			std::wcout << "<<  ";
		else std::wcout << "    ";
		int max_ic_page = owned_ic.size() > 0 ? (owned_ic.size() - 1) / 5 + 1 : 1;
		if (spell_deck_menu == spell_deck_menu_enum::Item_Cards)
			std::wcout << ">Page: " << ic_page << " / " << max_ic_page;
		else std::wcout << " Page: " << ic_page << " / " << max_ic_page;
		if (ic_page != max_ic_page)
			std::wcout << "   >>";

		choice = _getch();
		switch (choice) {
			case 'w':
			case ARROW_UP:
				switch (spell_deck_menu) {
					case spell_deck_menu_enum::Unlocked_Spells:
						spell_deck_menu = spell_deck_menu_enum::Deck;
						break;
					case spell_deck_menu_enum::Equipped_Treasure_Cards:
						spell_deck_menu = spell_deck_menu_enum::Unlocked_Spells;
						break;
					case spell_deck_menu_enum::Treasure_Cards:
						spell_deck_menu = spell_deck_menu_enum::Equipped_Treasure_Cards;
						break;
					case spell_deck_menu_enum::Item_Cards:
						spell_deck_menu = spell_deck_menu_enum::Treasure_Cards;
						break;
				}
				break;
			case 's':
			case ARROW_DOWN:
				switch (spell_deck_menu) {
				case spell_deck_menu_enum::Deck:
					spell_deck_menu = spell_deck_menu_enum::Unlocked_Spells;
					break;
				case spell_deck_menu_enum::Unlocked_Spells:
					spell_deck_menu = spell_deck_menu_enum::Equipped_Treasure_Cards;
					break;
				case spell_deck_menu_enum::Equipped_Treasure_Cards:
					spell_deck_menu = spell_deck_menu_enum::Treasure_Cards;
					break;
				case spell_deck_menu_enum::Treasure_Cards:
					spell_deck_menu = spell_deck_menu_enum::Item_Cards;
					break;
				}
				break;
			case 'a':
			case ARROW_LEFT:
				switch (spell_deck_menu) {
				case spell_deck_menu_enum::Deck:
					if (deck_page != 1)
						deck_page--;
					break;
				case spell_deck_menu_enum::Unlocked_Spells:
					if (spells_page != 1)
						spells_page--;
					break;
				case spell_deck_menu_enum::Equipped_Treasure_Cards:
					if (eq_tc_page != 1)
						eq_tc_page--;
					break;
				case spell_deck_menu_enum::Treasure_Cards:
					if (tc_page != 1)
						tc_page--;
					break;
				case spell_deck_menu_enum::Item_Cards:
					if (ic_page != 1)
						ic_page--;
					break;
				}
				break;
			case 'd':
			case ARROW_RIGHT:
				switch (spell_deck_menu) {
				case spell_deck_menu_enum::Deck:
					if (deck_page != max_deck_page)
						deck_page++;
					break;
				case spell_deck_menu_enum::Unlocked_Spells:
					if (spells_page != max_spells_page)
						spells_page++;
					break;
				case spell_deck_menu_enum::Equipped_Treasure_Cards:
					if (eq_tc_page != max_eq_tc_page)
						eq_tc_page++;
					break;
				case spell_deck_menu_enum::Treasure_Cards:
					if (tc_page != max_tc_page)
						tc_page++;
					break;
				case spell_deck_menu_enum::Item_Cards:
					if (ic_page != max_ic_page)
						ic_page++;
					break;
				}
				break;
			case 'p':
			case ESCAPE_KEY:
				loop = false;
				break;
			// TODO: add functionality to 1-5 keys
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
				switch (spell_deck_menu) {
				case spell_deck_menu_enum::Deck:
					if (choice - '1' + (deck_page - 1) * 5 < deck.spells.size())
						deck.RemoveSpell(deck.spells[choice - '1' + (deck_page - 1) * 5]);
					break;
				case spell_deck_menu_enum::Unlocked_Spells:
					if (choice - '1' + (spells_page - 1) * 5 < unlocked_spells.size())
						deck.AddSpell(unlocked_spells[choice - '1' + (spells_page - 1) * 5]);
					break;
				case spell_deck_menu_enum::Equipped_Treasure_Cards:
					if (choice - '1' + (eq_tc_page - 1) * 5 < player.GetEquippedTreasureCards().size())
						player.UnequipTreasureCard(player.GetEquippedTreasureCards()[choice - '1' + (eq_tc_page - 1) * 5]);
					break;
				case spell_deck_menu_enum::Treasure_Cards:
					if (choice - '1' + (tc_page - 1) * 5 < player.GetTreasureCards().size())
						player.EquipTreasureCard(player.GetTreasureCards()[choice - '1' + (tc_page - 1) * 5]);
					break;
				case spell_deck_menu_enum::Item_Cards:
					break;
				}
				break;
		}
	}
}