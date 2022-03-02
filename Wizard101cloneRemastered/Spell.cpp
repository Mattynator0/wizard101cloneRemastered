#include "Spell.h"

// ----- functions -----
std::istream& operator>> (std::istream& in, Spell& spell) {
	// input example
	// 1 Fire cat;1 1 1 75;80-120 outgoing fire dmg
	int temp_int;
	std::string temp_str;
	in >> spell.m_id; // 1
	in.ignore(1); // skip ' ' character
	std::getline(in, temp_str, ';'); // "Fire cat"
	spell.m_name = widen(temp_str);
	in >> spell.m_cost >> temp_int; // 1 1
	spell.m_school = (school_enum)temp_int; // Fire
	in >> temp_int; // 1
	spell.m_type = (spell_type_enum)temp_int; // Damage
	in >> spell.m_accuracy; // 75
	in.ignore(1); // skip ';' character
	std::getline(in, temp_str); // 80-120 outgoing fire dmg
	spell.m_descripition = widen(temp_str);
	return in;
}

// <-- encapsulation -->
int Spell::GetId() const { return m_id; }
std::wstring Spell::GetName() const { return m_name; }
int Spell::GetCost() const { return m_cost; }
school_enum Spell::GetSchool() const { return m_school; }
spell_type_enum Spell::GetType() const { return m_type; }
int Spell::GetAccuracy() const { return m_accuracy; }
std::wstring Spell::GetDescripition() const { return m_descripition; }

// makes it possible to access a spell knowing its 'id' value instead of index in array
Spell& SpellArray::operator() (const int id, card_type_enum card_type) {
	// TODO use a more efficient algorithm like std::binary_search
	switch (card_type) {
		case card_type_enum::Spell:
			return *std::find_if(spells.begin(), spells.end(), [&](Spell& spell) { return spell.GetId() == id; });
		case card_type_enum::Item_Card:
			return *std::find_if(item_cards.begin(), item_cards.end(), [&](Spell& spell) { return spell.GetId() == id; });
		case card_type_enum::Treasure_Card:
			return *std::find_if(treasure_cards.begin(), treasure_cards.end(), [&](Spell& spell) { return spell.GetId() == id; });
		default:
			std::cerr << "Incorrect card type";
			exit(0);
	}
}