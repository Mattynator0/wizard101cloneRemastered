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
	int GetId();
	std::string GetName();
	int GetMax_hp();
	int GetRank();
	school_enum GetSchool();
	int GetN_enemy_spells();
	std::vector<int> GetEnemy_spells();
	EnemyDrops GetDrops();

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
