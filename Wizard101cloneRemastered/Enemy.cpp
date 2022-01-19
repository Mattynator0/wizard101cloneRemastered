#include "Enemy.h"

// ----- functions -----
std::istream& operator>> (std::istream& in, Enemy& enemy) {
	int temp;
	in >> enemy.id >> enemy.name >> enemy.max_hp >> enemy.rank >> temp;
	enemy.school = (school_enum)temp;
	in >> enemy.n_enemy_spells;
	for (int i = 0; i < enemy.n_enemy_spells; i++) {
		in >> temp;
		enemy.enemy_spells.push_back(temp);
	}
	in >> enemy.drops.gold_min >> enemy.drops.gold_max >> enemy.drops.n_drops_items;
	for (int i = 0; i < enemy.drops.n_drops_items; i++) {
		in >> temp;
		enemy.drops.items_id.push_back(temp);
		in >> temp;
		enemy.drops.items_drop_rate.push_back(temp);
	}
	return in;
}

// <-- encapsulation -->
int Enemy::GetId() { return id; }
std::string Enemy::GetName() { return name; }
int Enemy::GetMax_hp() { return max_hp; }
int Enemy::GetRank() { return rank; }
school_enum Enemy::GetSchool() { return school; }
int Enemy::GetN_enemy_spells() { return n_enemy_spells; }
std::vector<int> Enemy::GetEnemy_spells() { return enemy_spells; }
EnemyDrops Enemy::GetDrops() { return drops; }
