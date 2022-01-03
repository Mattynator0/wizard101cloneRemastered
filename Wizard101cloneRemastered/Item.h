#pragma once
#include "my_globals.h"

#include <iostream>
#include <string>

const int n_items = 0;


class Item
{
	// ----- functions -----
public:
	friend std::istream& operator>> (std::istream& in, Item& item);

	// <-- encapsulation -->
	int Get_id();
	std::string Get_name();
	int Get_level_req();
	std::string Get_stats();

	// ----- data -----
protected:
	int id;
	std::string name;
	int level_req;
	school_enum school_req;
	std::string stats;
	
};

std::istream& operator>> (std::istream& in, Item& item);
