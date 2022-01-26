#pragma once
#include "my_globals.h"

#include <iostream>

const int n_items = 0;


class Item
{
	// ----- functions -----
public:
	friend std::istream& operator>> (std::istream& in, Item& item);

	// <-- encapsulation -->
	int GetId();
	std::wstring GetName();
	int GetLevel_req();
	std::wstring GetStats();

	// ----- data -----
protected:
	int m_id;
	std::wstring m_name;
	int m_level_req;
	school_enum m_school_req;
	std::wstring m_stats;
	
};

std::istream& operator>> (std::istream& in, Item& item);
