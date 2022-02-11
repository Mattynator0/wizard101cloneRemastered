#pragma once
#include "my_globals.h"

#include <array>
#include <iostream>

const int n_items = 115;


class Item
{
	// ----- functions -----
public:
	friend std::istream& operator>> (std::istream& in, Item& item);

	// <-- encapsulation -->
	int GetId();
	std::wstring GetName();
	item_type_enum GetType();
	int GetLevelReq();
	school_enum GetSchoolReq();
	std::wstring GetStats();

	// ----- data -----
protected:
	int m_id;
	std::wstring m_name;
	item_type_enum m_type;
	int m_level_req;
	school_enum m_school_req;
	std::wstring m_stats;
};

std::istream& operator>> (std::istream& in, Item& item);

struct ItemArray {
	std::array<Item, n_items> arr;
	Item& operator[] (const int id);
};