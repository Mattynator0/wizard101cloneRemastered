#include "Item.h"

// ----- functions -----
std::istream& operator>> (std::istream& in, Item& item) {
	// input example
	// 7001 Starter deck;8 0 0;deck size:14,3,5;
	int temp_int;
	std::string temp_str;
	in >> item.m_id; // 701
	in.ignore(1); // skip ' ' character
	std::getline(in, temp_str, ';'); // "Starter deck"
	item.m_name = widen(temp_str);
	in >> temp_int; // 8
	item.m_type = item_type_enum(temp_int); // Deck
	in >> item.m_level_req >> temp_int; // 0 0
	item.m_school_req = school_enum(temp_int); // None
	in.ignore(1); // skip ';' character
	std::getline(in, temp_str); // "deck size:14,3,5;"
	item.m_stats = widen(temp_str);
	return in;
}

// <-- encapsulation -->
int Item::GetId() const { return m_id; }
std::wstring Item::GetName() const { return m_name; }
item_type_enum Item::GetType() const { return m_type; }
int Item::GetLevelReq() const { return m_level_req; }
school_enum Item::GetSchoolReq() const { return m_school_req; }
std::wstring Item::GetStats() const { return m_stats; }