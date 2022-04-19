#include "Enemy.h"

// ----- functions -----
std::istream& operator>> (std::istream& in, Enemy& enemy) {
	int temp_int;
	std::string str;
	char ch;
	in >> enemy.m_id >> ch; // get id, skip ' ' character, get appearance character
	std::getline(in, str, ';');
	enemy.m_name = widen(str);
	in >> enemy.m_max_hp >> enemy.m_rank >> temp_int >> enemy.m_n_enemy_spells;
	enemy.m_appearance = wchar_t(ch);
	enemy.m_school = school_enum(temp_int);
	for (int i = 0; i < enemy.m_n_enemy_spells; i++) {
		in >> temp_int;
		enemy.m_enemy_spells.push_back(temp_int);
	}
	in >> enemy.m_drops.gold_min >> enemy.m_drops.gold_max >> enemy.m_drops.n_drops_items;
	for (int i = 0; i < enemy.m_drops.n_drops_items; i++) {
		in >> temp_int;
		enemy.m_drops.items_id.push_back(temp_int);
		in >> temp_int;
		enemy.m_drops.items_drop_rate.push_back(temp_int);
	}
	// FIXME include other things in drops (currently it's only wearables)
	return in;
}

// <-- encapsulation -->
int Enemy::GetId() const { return m_id; }
std::wstring Enemy::GetName() const { return m_name; }
int Enemy::GetHp() const { return m_hp; }
void Enemy::ResetHp() { m_hp = m_max_hp; }
int Enemy::GetMax_hp() const { return m_max_hp; }
int Enemy::GetRank() const { return m_rank; }
school_enum Enemy::GetSchool() const { return m_school; }
int Enemy::GetN_enemy_spells() const { return m_n_enemy_spells; }
std::vector<int> Enemy::GetEnemy_spells() const { return m_enemy_spells; }
EnemyDrops Enemy::GetDrops() const { return m_drops; }
