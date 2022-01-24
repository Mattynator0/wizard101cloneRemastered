#include "Spell.h"

// ----- functions -----
std::istream& operator>> (std::istream& in, Spell& spell) {
	int temp;
	in >> spell.id;
	in.ignore(1);
	getline(in, spell.name, ';');
	in >> spell.cost >> temp;
	spell.school = (school_enum)temp;
	in >> temp;
	spell.type = (spell_type_enum)temp;
	in >> spell.accuracy;
	in.ignore(1);
	getline(in, spell.descripition);
	return in;
}

// <-- encapsulation -->
int Spell::GetId() { return id; }
std::string Spell::GetName() { return name; }
int Spell::GetCost() { return cost; }
school_enum Spell::GetSchool() { return school; }
spell_type_enum Spell::GetType() { return type; }
int Spell::GetAccuracy() { return accuracy; }
std::string Spell::GetDescripition() { return descripition; }
