#pragma once
#include "my_globals.h"

#include <iostream>

const int n_spells = 1;

class Spell
{
	// ----- functions -----
public:
	friend std::istream& operator>> (std::istream& in, Spell& spell);

	// <-- encapsulation -->
	int GetId();
	std::wstring GetName();
	int GetCost();
	school_enum GetSchool();
	spell_type_enum GetType();
	int GetAccuracy();
	std::wstring GetDescripition();


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
