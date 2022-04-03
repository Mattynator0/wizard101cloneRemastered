#pragma once
#include "my_globals.h"

#include <iostream>

class Item
{
	// ----- functions -----
public:
	friend std::istream& operator>> (std::istream& in, Item& item);

	// <-- encapsulation -->
	int GetId() const;
	std::wstring GetName() const;
	item_type_enum GetType() const;
	int GetLevelReq() const;
	school_enum GetSchoolReq() const;
	std::wstring GetStats() const;

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