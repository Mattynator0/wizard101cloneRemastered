#pragma once
#include "my_globals.h"

#include <iostream>

class Spell
{
	// ----- functions -----
public:
	friend std::istream& operator>> (std::istream& in, Spell& spell);

	// <-- encapsulation -->
	int GetId() const;
	std::wstring GetName() const;
	int GetCost() const;
	school_enum GetSchool() const;
	spell_type_enum GetSpellType() const;
	void SetCardType(card_type_enum card_type);
	card_type_enum GetCardType() const;
	int GetAccuracy() const;
	std::wstring GetDescripition() const;


	// ----- data -----
protected:
	int m_id;
	std::wstring m_name;
	int m_cost;
	school_enum m_school;
	spell_type_enum m_spell_type;
	card_type_enum m_card_type;
	int m_accuracy;
	std::wstring m_descripition;
	
};

std::istream& operator>> (std::istream& in, Spell& spell);

struct SpellsData {
	std::unordered_map<int, Spell> spell;
	std::unordered_map<int, Spell> ic; // item cards
	std::unordered_map<int, Spell> tc; // treasure cards

};
std::wostream& operator<< (std::wostream& out, Spell& spell);