#include "Spell.h"

// ----- functions -----
std::istream& operator>> (std::istream& in, Spell& spell) {
	int temp;
	in >> spell.id >> spell.name >> spell.cost >> temp;
	spell.school = (school_enum)temp;
	in >> temp;
	spell.type = (spell_type_enum)temp;
	in >> spell.accuracy >> spell.descripition;
	return in;
}

// <-- encapsulation -->
int Spell::Get_id() { return id; }
std::string Spell::Get_name() { return name; }
int Spell::Get_cost() { return cost; }
school_enum Spell::Get_school() { return school; }
spell_type_enum Spell::Get_type() { return type; }
int Spell::Get_accuracy() { return accuracy; }
std::string Spell::Get_descripition() { return descripition; }
