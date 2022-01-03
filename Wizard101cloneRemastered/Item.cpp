#include "Item.h"

// ----- functions -----
std::istream& operator>> (std::istream& in, Item& item) {
	in >> item.id >> item.name >> item.level_req;
	int temp_int;
	in >> temp_int;
	item.school_req = school_enum(temp_int);
	in >> item.stats;
	return in;
}

// <-- encapsulation -->
int Item::Get_id() { return id; }
std::string Item::Get_name() { return name; }
int Item::Get_level_req() { return level_req; }
std::string Item::Get_stats() { return stats; }
