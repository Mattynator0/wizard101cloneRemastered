#include "Spell.h"

// ----- functions -----
std::istream& operator>> (std::istream& in, Spell& spell) {
	// input example
	// 1 Scarab;1 7 1 85 65-105 outgoing balance dmg
	int temp_int;
	std::string temp_str;
	in >> spell.m_id; // 1
	in.ignore(1); // skip ' ' character
	std::getline(in, temp_str, ';'); // "Scarab"
	spell.m_name = widen(temp_str);
	in >> spell.m_cost >> temp_int; // 1 7
	spell.m_school = (school_enum)temp_int;
	in >> temp_int; // 1
	spell.m_type = (spell_type_enum)temp_int;
	in >> spell.m_accuracy; // 85
	in.ignore(1); // skip ' ' character
	std::getline(in, temp_str); // 65 - 105 outgoing balance dmg
	spell.m_descripition = widen(temp_str);
	return in;
}

// <-- encapsulation -->
int Spell::GetId() { return m_id; }
std::wstring Spell::GetName() { return m_name; }
int Spell::GetCost() { return m_cost; }
school_enum Spell::GetSchool() { return m_school; }
spell_type_enum Spell::GetType() { return m_type; }
int Spell::GetAccuracy() { return m_accuracy; }
std::wstring Spell::GetDescripition() { return m_descripition; }
