#include "Item.h"

// ----- functions -----
std::istream& operator>> (std::istream& in, Item& item) {
	int temp_int;
	std::string temp_str;
	in >> item.m_id >> temp_str;
	item.m_name = widen(temp_str);
	in >> item.m_level_req;
	in >> temp_int;
	item.m_school_req = school_enum(temp_int);
	in >> temp_str;
	item.m_stats = widen(temp_str);
	return in;
}

// <-- encapsulation -->
int Item::GetId() { return m_id; }
std::wstring Item::GetName() { return m_name; }
int Item::GetLevel_req() { return m_level_req; }
std::wstring Item::GetStats() { return m_stats; }
