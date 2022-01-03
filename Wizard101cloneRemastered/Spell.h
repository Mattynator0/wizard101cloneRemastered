#pragma once
#include "my_globals.h"

#include <iostream>
#include <string>

const int n_spells = 0;

class Spell
{
	// ----- functions -----
public:
	friend std::istream& operator>> (std::istream& in, Spell& spell);

	// <-- encapsulation -->
	int Get_id();
	std::string Get_name();
	int Get_cost();
	school_enum Get_school();
	spell_type_enum Get_type();
	int Get_accuracy();
	std::string Get_descripition();


	// ----- data -----
protected:
	int id;
	std::string name;
	int cost;
	school_enum school;
	spell_type_enum type;
	int accuracy;
	std::string descripition;
	
};

std::istream& operator>> (std::istream& in, Spell& spell);
