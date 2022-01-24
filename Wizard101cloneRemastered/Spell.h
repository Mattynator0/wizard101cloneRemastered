#pragma once
#include "my_globals.h"

#include <iostream>
#include <string>

const int n_spells = 1;

class Spell
{
	// ----- functions -----
public:
	friend std::istream& operator>> (std::istream& in, Spell& spell);

	// <-- encapsulation -->
	int GetId();
	std::string GetName();
	int GetCost();
	school_enum GetSchool();
	spell_type_enum GetType();
	int GetAccuracy();
	std::string GetDescripition();


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
