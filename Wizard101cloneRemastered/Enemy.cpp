#include "Enemy.h"

// ----- functions -----
std::istream& operator>> (std::istream& in, Enemy& enemy) {
	int temp;
	std::string temp_str;
	char temp_char;
	in >> enemy.m_id >> temp_char >> temp_str >> enemy.m_max_hp >> enemy.m_rank >> temp >> enemy.m_n_enemy_spells;
	enemy.m_appearance = wchar_t(temp_char);
	enemy.m_name = widen(temp_str);
	enemy.m_school = (school_enum)temp;
	for (int i = 0; i < enemy.m_n_enemy_spells; i++) {
		in >> temp;
		enemy.m_enemy_spells.push_back(temp);
	}
	in >> enemy.m_drops.gold_min >> enemy.m_drops.gold_max >> enemy.m_drops.n_drops_items;
	for (int i = 0; i < enemy.m_drops.n_drops_items; i++) {
		in >> temp;
		enemy.m_drops.items_id.push_back(temp);
		in >> temp;
		enemy.m_drops.items_drop_rate.push_back(temp);
	}
	return in;
}

// <-- encapsulation -->
int Enemy::GetId() { return m_id; }
std::wstring Enemy::GetName() { return m_name; }
int Enemy::GetMax_hp() { return m_max_hp; }
int Enemy::GetRank() { return m_rank; }
school_enum Enemy::GetSchool() { return m_school; }
int Enemy::GetN_enemy_spells() { return m_n_enemy_spells; }
std::vector<int> Enemy::GetEnemy_spells() { return m_enemy_spells; }
EnemyDrops Enemy::GetDrops() { return m_drops; }
