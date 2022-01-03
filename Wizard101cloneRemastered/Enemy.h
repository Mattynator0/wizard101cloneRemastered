#pragma once
#include "Entity.h"

#include <iostream>
#include <string>
#include <vector>

const int n_enemies = 0;

struct EnemyDrops {
	int gold_min;
	int gold_max;
	int n_drops_items;
	std::vector<int> items_id;
	std::vector<int> items_drop_rate;
};

class Enemy :
    public Entity
{
	// ----- functions -----
public:
	// !!!!! FIXME read enemy appearance from file
	friend std::istream& operator>> (std::istream& in, Enemy& enemy);

	// <-- encapsulation -->
	int Get_id();
	std::string Get_name();
	int Get_max_hp();
	int Get_rank();
	school_enum Get_school();
	int Get_n_enemy_spells();
	std::vector<int> Get_enemy_spells();
	EnemyDrops Get_drops();

	// ----- data -----
protected:
	int id;
	std::string name;
	int max_hp;
	int rank;
	school_enum school;
	int n_enemy_spells;
	std::vector<int> enemy_spells;
	EnemyDrops drops;

};

std::istream& operator>> (std::istream& in, Enemy& enemy);
