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

// ----- loading stuff in from files (spells, items, etc.) -----
void LoadData() {
	std::ifstream in;

	Spell temp_spell;
	in.open("Data/Spells/spells.txt");
	while (in.peek() != EOF) {
		in >> temp_spell;
		temp_spell.SetCardType(card_type_enum::Spell);
		spells.spell[temp_spell.GetId()] = temp_spell;
	}
	in.close();

	in.open("Data/Spells/itemcards.txt");
	while (in.peek() != EOF) {
		in >> temp_spell;
		temp_spell.SetCardType(card_type_enum::Item_Card);
		spells.ic[temp_spell.GetId()] = temp_spell;
	}
	in.close();

	in.open("Data/Spells/treasurecards.txt");
	while (in.peek() != EOF) {
		in >> temp_spell;
		temp_spell.SetCardType(card_type_enum::Treasure_Card);
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
	while (true) {
		system("CLS");
		current_level.DrawLevel();
		char choice = _getch();
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
			BeginBattle(enemy_ptr);
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
void SpellOnPlayer(const Spell& spell) {
	std::wstring desc = spell.GetDescripition();
	switch (spell.GetSpellType()) {
		case spell_type_enum::Damage:
			// TODO make enemies' blades increase dealt damage
			int min_dmg, max_dmg;
			bool is_dot = false; // DoT - Damage over Time
			bool is_necromancy = false; // necromancy converts half of dealt dmg to healing
			int n_hits = 1; // number of hits this round
			std::vector<school_enum> hits_school; // school type of every hit (DoT is the same type as main attack)

			// e.g. "50 Myth damage and 445 Myth damage"
			if (desc.find(L" damage and ") != std::wstring::npos) {
				n_hits = 2;
				min_dmg = std::stoi(desc.substr(0, desc.find(' '))); // this now means 1st hit damage
				desc.erase(0, desc.find(' ') + 1);
				hits_school.push_back(map_wstr_school[desc.substr(0, desc.find(' '))]);
				desc.erase(0, desc.find(L" and ") + 5);
				max_dmg = std::stoi(desc.substr(0, desc.find(' '))); // this now means 2nd hit damage
				desc.erase(0, desc.find(' ') + 1);
				hits_school.push_back(map_wstr_school[desc.substr(0, desc.find(' '))]);
				desc.erase(0, desc.find(L"damage") + 6);

				player.ReceiveDamage(min_dmg, hits_school[0]);
				player.ReceiveDamage(max_dmg, hits_school[1]);
			}
			// e.g. "190 Fire, Ice and Storm damage"
			else if (desc.find(L" and ") < desc.find(L" damage")) {
				n_hits = 3;
				min_dmg = std::stoi(desc.substr(0, desc.find(' ')));
				desc.erase(0, desc.find(' ') + 1);
				max_dmg = min_dmg;
				hits_school.push_back(map_wstr_school[desc.substr(0, desc.find(' '))]);
				desc.erase(0, desc.find(' ') + 1);
				hits_school.push_back(map_wstr_school[desc.substr(0, desc.find(' '))]);
				desc.erase(0, desc.find(' ') + 1);
				hits_school.push_back(map_wstr_school[desc.substr(0, desc.find(' '))]);
				desc.erase(0, desc.find(L"damage") + 6);

				player.ReceiveDamage(min_dmg, hits_school[0]);
				player.ReceiveDamage(min_dmg, hits_school[1]);
				player.ReceiveDamage(min_dmg, hits_school[2]);
			}
			// e.g. "440 Fire, 365 Ice or 550 Storm damage"
			else if (desc.find(L" or ") < desc.find(L" damage")) {
				int which = RNG<int>(0, 2);
				if (which == 2) {
					desc.erase(0, desc.find(L" or ") + 4);
					min_dmg = std::stoi(desc.substr(0, desc.find(' ')));
					desc.erase(0, desc.find(' ') + 1);
					max_dmg = min_dmg;
					hits_school.push_back(map_wstr_school[desc.substr(0, desc.find(' '))]);
					desc.erase(0, desc.find(L"damage") + 6);
				}
				else {
					for (int i = 0; i < 2; i++) {
						int damage = std::stoi(desc.substr(0, desc.find(' ')));
						desc.erase(0, desc.find(' ') + 1);
						std::wstring school_str = desc.substr(0, desc.find(','));
						desc.erase(0, desc.find(' ') + 1);

						if (i == which) {
							min_dmg = damage;
							max_dmg = damage;
							hits_school.push_back(map_wstr_school[school_str]);
						}
						break;
					}
					desc.erase(0, desc.find(L"damage") + 6);
				}

				player.ReceiveDamage(min_dmg, hits_school[0]);
			}
			// e.g. "160 Death damage, swap half to healing"
			else if (desc.find(L" swap half ") != std::wstring::npos) {
				is_necromancy = true;
				min_dmg = std::stoi(desc.substr(0, desc.find(' ')));
				desc.erase(0, desc.find(' ') + 1);
				max_dmg = min_dmg;
				hits_school.push_back(map_wstr_school[desc.substr(0, desc.find(' '))]);
				desc.erase(0, desc.find(L"healing") + 7);

				player.ReceiveDamage(min_dmg, hits_school[0]);
				// TODO heal enemy
			}
			// e.g. "80-120 Fire damage"
			else if (desc.find('-') < desc.find(' ') && desc.find('-') < desc.find('+')) {
				min_dmg = std::stoi(desc.substr(0, desc.find('-')));
				desc.erase(0, desc.find('-') + 1);
				max_dmg = std::stoi(desc.substr(0, desc.find(' ')));
				desc.erase(0, desc.find(' ') + 1);
				hits_school.push_back(map_wstr_school[desc.substr(0, desc.find(' '))]);
				desc.erase(0, desc.find(L"damage") + 6);

				int damage = min_dmg + (max_dmg - min_dmg) * RNG<int>(0, 4) / 4;
				player.ReceiveDamage(damage, hits_school[0]);
			}
			// e.g. "100+210 Fire damage over 3 rounds"
			else if (desc.find('+') < desc.find(' ')) {
				is_dot = true;
				min_dmg = std::stoi(desc.substr(0, desc.find('+'))); // this now means damage in this round
				desc.erase(0, desc.find('+') + 1);
				max_dmg = std::stoi(desc.substr(0, desc.find(' '))); // this now means total damage spread over next 3 rounds
				desc.erase(0, desc.find(' ') + 1);
				hits_school.push_back(map_wstr_school[desc.substr(0, desc.find(' '))]);
				desc.erase(0, desc.find(L"rounds") + 6);

				player.ReceiveDamage(min_dmg, hits_school[0]);
				// TODO add DoT
			}
			// e.g. "50 Fire damage"
			else {
				min_dmg = std::stoi(desc.substr(0, desc.find(' ')));
				max_dmg = min_dmg;
				desc.erase(0, desc.find(' ') + 1);
				hits_school.push_back(map_wstr_school[desc.substr(0, desc.find(' '))]);
				desc.erase(0, desc.find(L"damage") + 6);

				player.ReceiveDamage(min_dmg, hits_school[0]);
			}

			break;
	}
}
void SpellOnEnemy(const Spell& spell, Enemy* enemy_ptr) {

}
void BeginBattle(Enemy* enemy_ptr) {
	enemy_ptr->ResetHp(); // make sure enemy has full hp
	enemy_ptr->ResetPips();
	player.ResetPips();
	std::vector<Spell> hand; // 'Spell' data type is used so that data doesn't need to be fetched from 'spells' every time
	std::vector<int> pile[2];
	std::vector<int>& pile_tc = player.GetDeckRef().treasure_cards; // reference needed since tc's are single-use
	
	// spells
	pile[0] = player.GetDeck().spells;
	
	// ic
	pile[1] = player.GetItemCards();

	bool coinflip = RNG<int>(0, 1); // 1 - player goes first, 0 - enemy goes first
	char choice;
	while (enemy_ptr->GetHp() > 0 && player.GetHp() > 0) {
		player.GainPip();
		enemy_ptr->GainPip();
		// FIXME enemy should start with some set amount of pips

		// draw cards from pile until hand is full (7) or there are no more cards to draw
		while (hand.size() < 7 && pile[0].size() + pile[1].size() > 0) {
			int n = RNG<int>(0, pile[0].size() + pile[1].size() - 1);
			if (n < pile[0].size()) {
				hand.push_back(spells.spell.at(pile[0][n]));
				pile[0].erase(pile[0].begin() + n);
			}
			else hand.push_back(spells.ic.at(pile[1][n - pile[0].size()]));
			pile[1].erase(pile[1].begin() + n - pile[0].size());
		}

		system("CLS");
		
		// display info about enemy
		std::wcout << enemy_ptr->GetName() << "\nHealth: " << enemy_ptr->GetHp() << "/" << enemy_ptr->GetMax_hp() 
				   << "\nPips: " << enemy_ptr->GetPips() << "\n\n\n";

		// display cards in hand
		for (int i = 0; i < hand.size(); i++) {
			std::wcout << i + 1 << ". " << hand[i] << "\n";
		}

		// choose a card to play
		// FIXME this may break if 'hand' is empty
		// TODO add option to draw a tc
		// TODO use the GetInput() function (it's currently commented out)
		do {
			choice = _getch();
		} while (choice < '1' || choice > hand.size() + '0' || !player.IsSpellAffordable(hand[choice - '1']));

		Spell& spell = hand[choice - '1'];

		if (coinflip) {
			if (RNG<int>(1, 100) <= spell.GetAccuracy() + player.GetAccuracy()[int(spell.GetSchool()) - 1]) {
				SpellOnEnemy(spell, enemy_ptr);
				hand.erase(hand.begin() + choice - '1');
			}
			else {
				// move the spell back to pile
				if (spell.GetCardType() == card_type_enum::Item_Card)
					pile[1].push_back(spell.GetId());
				else pile[0].push_back(spell.GetId());

				hand.erase(hand.begin() + choice - '1');
			}

			// check if enemy died

			// TODO add enemies' AI

			// check if player died
		}
		else {
			// TODO add enemies' AI
			
			// check if player died

			if (RNG<int>(1, 100) <= spell.GetAccuracy() + player.GetAccuracy()[int(spell.GetSchool()) - 1]) {
				//player.UseSpell(enemy_ptr);
				hand.erase(hand.begin() + choice - '1');
			}
			else {
				if (spell.GetCardType() == card_type_enum::Treasure_Card)
					pile[1].push_back(spell.GetId());
				else pile[0].push_back(spell.GetId());

				hand.erase(hand.begin() + choice - '1');
			}

			// check if enemy died
		}
	}
}
void SpellDeckMenu() {
	int page[5] = { 1,1,1,1,1 }; // deck, unlocked spells, equipped tc, owned tc, ic
	int max_page[5];
	auto current_menu = spell_deck_menu_enum::Deck;
	bool loop = true;
	while (loop) {
		auto& deck			 = player.GetDeckRef();
		auto unlocked_spells = player.GetUnlockedSpells();
		auto& eq_tc			 = deck.treasure_cards;
		auto owned_tc		 = player.GetTreasureCards(); // doesn't include eq_tc; FIXME determine if a reference is needed here
		auto owned_ic		 = player.GetItemCards();

		max_page[0] = deck.spells.size()	 > 0 ? (deck.spells.size() - 1)		/ 5 + 1 : 1;
		max_page[1] = unlocked_spells.size() > 0 ? (unlocked_spells.size() - 1) / 5 + 1 : 1;
		max_page[2] = eq_tc.size()			 > 0 ? (eq_tc.size() - 1)			/ 5 + 1 : 1;
		max_page[3] = owned_tc.size()		 > 0 ? (owned_tc.size() - 1)		/ 5 + 1 : 1;
		max_page[4] = owned_ic.size()		 > 0 ? (owned_ic.size() - 1)		/ 5 + 1 : 1;

		int menu_int = (int)current_menu - 1;
		page[menu_int] = page[menu_int] > max_page[menu_int] ? max_page[menu_int] : page[menu_int];

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
				auto spell = spells.spell.at(deck.spells[(page[0] - 1) * 5 + i]);
				// Fire cat    Cost: 1    School: Fire    Accuracy: 75    80-120 Fire damage
				std::wcout << spell << "\n";
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
				
				auto spell = spells.spell.at(unlocked_spells[(page[1] - 1) * 5 + i]);
				// Fire cat    Cost: 1    School: Fire    Accuracy: 75    80-120 Fire damage
				std::wcout << spell << "\n";
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

				auto spell = spells.tc.at(eq_tc[(page[2] - 1) * 5 + i]);
				// Fire cat    Cost: 1    School: Fire    Accuracy: 75    80-120 Fire damage
				std::wcout << spell << "\n";
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

				auto spell = spells.tc.at(owned_tc[(page[3] - 1) * 5 + i]);
				// Fire cat    Cost: 1    School: Fire    Accuracy: 75    80-120 Fire damage
				std::wcout << spell << "\n";
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

				auto spell = spells.ic.at(owned_ic[(page[4] - 1) * 5 + i]);
				// Fire cat    Cost: 1    School: Fire    Accuracy: 75    80-120 Fire damage
				std::wcout << spell << "\n";
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

		char choice = _getch();
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