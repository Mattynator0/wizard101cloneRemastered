#pragma once
#include "Entity.h"

#include <iostream>
#include <vector>

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
	friend std::istream& operator>> (std::istream& in, Enemy& enemy);

	// <-- encapsulation -->
	int GetId() const;
	std::wstring GetName() const;
	int GetHp() const;
	void ResetHp();
	int GetMax_hp() const;
	int GetRank() const;
	school_enum GetSchool() const;
	int GetN_enemy_spells() const;
	std::vector<int> GetEnemy_spells() const;
	EnemyDrops GetDrops() const;

	// ----- data -----
protected:
	int m_id;
	std::wstring m_name;
	int m_hp;
	int m_max_hp;
	int m_rank;
	school_enum m_school;
	int m_n_enemy_spells;
	std::vector<int> m_enemy_spells;
	EnemyDrops m_drops;

};

std::istream& operator>> (std::istream& in, Enemy& enemy);