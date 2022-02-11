#pragma once
#include "my_globals.h"

#include <algorithm>
#include <array>
#include <iostream>

const int n_spells = 22;

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
	spell_type_enum GetType() const;
	int GetAccuracy() const;
	std::wstring GetDescripition() const;


	// ----- data -----
protected:
	int m_id;
	std::wstring m_name;
	int m_cost;
	school_enum m_school;
	spell_type_enum m_type;
	int m_accuracy;
	std::wstring m_descripition;
	
};

std::istream& operator>> (std::istream& in, Spell& spell);

struct SpellArray {
	std::array<Spell, n_spells> arr;
	Spell& operator[] (const int id);
};