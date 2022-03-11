#include "Player.h"

void Deck::AddSpell(int id) {
	if (spells.size() < max_spell_count && GetSpellCount(id) < max_copies)
	{
		spells.push_back(id);
		std::sort(spells.begin(), spells.end());
	}
}
void Deck::RemoveSpell(int id) {

}
int Deck::GetSpellCount(int id) {
	auto first = std::distance(spells.begin(), std::lower_bound(spells.begin(), spells.end(), id)); // index of the first value equal to 'id'
	if (first == spells.size() || spells[first] != id)
		return 0;
	return std::distance(spells.begin(), std::upper_bound(spells.begin(), spells.end(), id)) - first + 1; // count of values equal to 'id'
}
void Deck::Clear() {
	max_spell_count = 0;
	max_copies = 0;
	spells.clear();
}

Player player(L"Mattynator", school_enum::Fire);

Player::Player(const std::wstring& name, const school_enum school) : m_name(name), m_school(school) {
	m_equipped_items.fill(nullptr);
	UpdateStats();
	m_hp = m_maxhp;
	m_mana = m_maxmana;
}

std::wstring& Player::GetName() { return m_name; }
school_enum Player::GetSchool() const { return m_school; }
int Player::GetLevel() const { return m_level; }

int Player::GetExp() const { return m_exp; }
struct LevelCap {
	int level, cap;
	bool training_point;
};
std::array<LevelCap, 49> levelcaps{ {
	{ 1,  45,    0 },
	{ 2,  115,   0 },
	{ 3,  205,   0 },
	{ 4,  340,   1 },
	{ 5,  495,   0 },
	{ 6,  670,   0 },
	{ 7,  875,   0 },
	{ 8,  1160,  1 },
	{ 9,  1400,  0 },
	{ 10, 1665,  0 },
	{ 11, 1950,  0 },
	{ 12, 2255,  1 },
	{ 13, 2580,  0 },
	{ 14, 2925,  0 },
	{ 15, 3520,  0 },
	{ 16, 3925,  1 },
	{ 17, 4350,  0 },
	{ 18, 4800,  0 },
	{ 19, 5270,  0 },
	{ 20, 5760,  1 },
	{ 21, 6270,  0 },
	{ 22, 6900,  0 },
	{ 23, 7640,  0 },
	{ 24, 8040,  0 },
	{ 25, 8640,  1 },
	{ 26, 9265,  0 },
	{ 27, 9905,  0 },
	{ 28, 10575, 0 },
	{ 29, 12055, 0 },
	{ 30, 12895, 1 },
	{ 31, 13820, 0 },
	{ 32, 14825, 0 },
	{ 33, 15920, 0 },
	{ 34, 17055, 0 },
	{ 35, 18220, 1 },
	{ 36, 19760, 0 },
	{ 37, 21005, 0 },
	{ 38, 22290, 0 },
	{ 39, 23610, 0 },
	{ 40, 24965, 1 },
	{ 41, 26350, 0 },
	{ 42, 27775, 0 },
	{ 43, 31085, 0 },
	{ 44, 32775, 0 },
	{ 45, 34510, 1 },
	{ 46, 36290, 0 },
	{ 47, 38110, 0 },
	{ 48, 39975, 0 },
	{ 49, 41880, 0 }
} };
void Player::AddExp(const int n) {
	m_exp += n;
	while (levelcaps[m_level - 1].cap >= m_exp) {
		if (levelcaps[m_level].training_point)
			m_training_points++;
		m_exp -= levelcaps[m_level - 1].cap;
		m_level += 1;
	}
}

std::vector<int> Player::GetUnlockedSpells() const { return m_unlocked_spells; }
void Player::UnlockSpell(int id) {
	m_unlocked_spells.push_back(id);
	std::sort(m_unlocked_spells.begin(), m_unlocked_spells.end());
}
std::vector<int> Player::GetItemsInBackpack() const { return m_items_in_backpack; }
void Player::AddItem(int id) {
	if (m_items_in_backpack.size() < 100)
		m_items_in_backpack.push_back(id);
	// else display that backpack is full
}
std::array<Item*, 8> Player::GetEquippedItems() const { return m_equipped_items; }
void Player::EquipItem(Item* item_ptr) {
	if (item_ptr->GetLevelReq() <= m_level && (item_ptr->GetSchoolReq() == m_school || item_ptr->GetSchoolReq() == school_enum::None))
		m_equipped_items[int(item_ptr->GetType())] = item_ptr;
	UpdateStats();
}
void Player::ClearStats() {
	m_hp = 0;
	m_maxhp = 0;
	m_mana = 0;
	m_maxmana = 0;
	m_powerpip_chance = 0;
	m_damage_raw.fill(0);
	m_damage_percentage.fill(0);
	m_resistance_raw.fill(0);
	m_resistance_percentage.fill(0);
	m_accuracy_raw.fill(0);
	m_accuracy_percentage.fill(0);
	m_healing_in = 0;
	m_healing_out = 0;
	m_item_cards.clear();
	m_deck.Clear();
}
void Player::UpdateStats() {
	std::vector<int> temp_vec = m_deck.spells;
	ClearStats();
	// level-based stats
	// equations are based on data from https://wizard101.fandom.com/wiki/Level_Chart
	m_maxmana = 15 + (m_level - 1) * 120 / 49;
	if (m_level >= 10)
		m_powerpip_chance = 10 + (m_level - 1) * 30 / 40;
	else m_powerpip_chance = 0;

	switch (m_school) {
		case school_enum::Fire:
			m_maxhp = 415 + (m_level - 1) * 1085 / 49;
			break;
		case school_enum::Ice:
			m_maxhp = 500 + (m_level - 1) * 1525 / 49;
			break;
		case school_enum::Storm:
			m_maxhp = 400 + (m_level - 1) * 800 / 49;
			break;
		case school_enum::Myth:
			m_maxhp = 425 + (m_level - 1) * 1075 / 49;
			break;
		case school_enum::Life:
			m_maxhp = 460 + (m_level - 1) * 1340 / 49;
			break;
		case school_enum::Death:
			m_maxhp = 450 + (m_level - 1) * 1200 / 49;
			break;
		case school_enum::Balance:
			m_maxhp = 480 + (m_level - 1) * 1320 / 49;
			break;
	}
	// items-based stats
	for (const auto& item : m_equipped_items) {
		if (!item)
			continue;
		std::wstring stats = item->GetStats();
		while (stats != L"") {
			// string structure:  stat1;stat2;...;
			// get all the info about first stat in string
			std::wstring current_stat = stats.substr(0, stats.find(';'));
			// erase it and the separator ';' from "master string"
			stats.erase(0, stats.find(';') + 1);

			// get the first keyword
			std::wstring current_stat_type = current_stat.substr(0, current_stat.find(':'));
			// erase it and the separator ':' from current stat string
			current_stat.erase(0, current_stat.find(':') + 1);

			if (current_stat_type == L"health") {
				m_maxhp += std::stoi(current_stat);
			} else
			if (current_stat_type == L"mana") {
				m_maxmana += std::stoi(current_stat);
			} else
			if (current_stat_type == L"damage") {
				current_stat_type = current_stat.substr(0, current_stat.find(':'));
				current_stat.erase(0, current_stat.find(':') + 1);

				// convert wstring to school_enum
				school_enum temp_school_enum;
				for (const auto& n : map_wstring_to_school) {
					if (current_stat_type == n.first) {
						temp_school_enum = n.second;
						break;
					}
				}

				// increment the correct variable
				if (current_stat.back() == '%') {
					current_stat.pop_back();
					m_damage_percentage[int(temp_school_enum)] += std::stoi(current_stat);
				}
				else {
					m_damage_raw[int(temp_school_enum)] += std::stoi(current_stat);
				}
			} else
			if (current_stat_type == L"resistance") {
				current_stat_type = current_stat.substr(0, current_stat.find(':'));
				current_stat.erase(0, current_stat.find(':') + 1);

				// convert wstring to school_enum
				school_enum temp_school_enum = school_enum::None;
				for (const auto& n : map_wstring_to_school) {
					if (current_stat_type == n.first) {
						temp_school_enum = n.second;
						break;
					}
				}

				// increment the correct variable
				if (current_stat.back() == '%') {
					current_stat.pop_back();
					m_resistance_percentage[int(temp_school_enum)] += std::stoi(current_stat);
				}
				else {
					m_resistance_raw[int(temp_school_enum)] += std::stoi(current_stat);
				}
			} else
			if (current_stat_type == L"accuracy") {
				current_stat_type = current_stat.substr(0, current_stat.find(':'));
				current_stat.erase(0, current_stat.find(':') + 1);
				
				// convert wstring to school_enum
				school_enum temp_school_enum;
				for (const auto& n : map_wstring_to_school) {
					if (current_stat_type == n.first) {
						temp_school_enum = n.second;
						break;
					}
				}

				// increment the correct variable
				if (current_stat.back() == '%') {
					current_stat.pop_back();
					m_accuracy_percentage[int(temp_school_enum)] += std::stoi(current_stat);
				}
				else {
					m_accuracy_raw[int(temp_school_enum)] += std::stoi(current_stat);
				}
			} else
			if (current_stat_type == L"spell") {
				// TODO add a separate part of a deck for itemcards
				while (current_stat != L"") {
					current_stat_type = current_stat.substr(0, current_stat.find(','));
					current_stat.erase(0, current_stat.find(',') + 1);
					m_item_cards.push_back(std::stoi(current_stat_type));
				}
			} else
			if (current_stat_type == L"deck size") {
				m_deck.max_spell_count = std::stoi(current_stat.substr(0, current_stat.find(',')));
				current_stat.erase(0, stats.find(',') + 1);
				m_deck.max_copies = std::stoi(current_stat.substr(0, current_stat.find(',')));

				// find the longest sequence of the same numbers
				int longest_seq = 0;
				int n = -1, count;
				for (int i : temp_vec) {
					if (i != n) {
						count = 0;
						n = i;
					}
					else count++;
					if (count > longest_seq)
						longest_seq = count;
				}
				// if the deck is large enough, copy the spells back into it
				if (m_deck.max_spell_count >= temp_vec.size() && m_deck.max_copies >= longest_seq)
					m_deck.spells = temp_vec;
			}
		}
	}
}

int Player::GetHp() const { return m_hp; }
int Player::GetMaxhp() const { return m_maxhp; }
int Player::GetMana() const { return m_mana; }
int Player::GetMaxmana() const { return m_maxmana; }
int Player::GetPowerpipChance() const { return m_powerpip_chance; }
int Player::GetTrainingPoints() const { return m_training_points; }
int Player::GetGold() const { return m_gold; }
std::array<int, 7> Player::GetDamageRaw() const { return m_damage_raw; }
std::array<int, 7> Player::GetDamagePercentage() const { return m_damage_percentage; }
std::array<int, 7> Player::GetResistanceRaw() const { return m_resistance_raw; }
std::array<int, 7> Player::ResistancePercentage() const { return m_resistance_percentage; }
std::array<int, 7> Player::GetAccuracyRaw() const { return m_accuracy_raw; }
std::array<int, 7> Player::GetAccuracyPercentage() const { return m_accuracy_percentage; }
int Player::GetHealingIn() const { return m_healing_in; }
int Player::GetHealingOut() const { return m_healing_out; }
Deck Player::GetDeck() const { return m_deck; }
std::vector<int> Player::GetItemCards() const { return m_item_cards; }
std::vector<int> Player::GetEquippedTreasureCards() const { return m_equipped_treasure_cards; }