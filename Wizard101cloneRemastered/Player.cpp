#include "Player.h"

Player player("Mattynator");

Player::Player(const std::string& name) : m_name(name) {}

std::string& Player::GetName() { return m_name; }
int Player::GetLevel() { return m_level; }
int Player::GetExp() { return m_exp; }

struct LevelCap {
	int level, cap;
	bool training_point;
};

std::array<LevelCap, 49> levelcaps{ {
	{ 1,  45,    0 },
	{ 2,  115,   0 },
	{ 3,  205,   0 },
	{ 4,  340,   1 },
	{ 5,  495,   0 },
	{ 6,  670,   0 },
	{ 7,  875,   0 },
	{ 8,  1160,  1 },
	{ 9,  1400,  0 },
	{ 10, 1665,  0 },
	{ 11, 1950,  0 },
	{ 12, 2255,  1 },
	{ 13, 2580,  0 },
	{ 14, 2925,  0 },
	{ 15, 3520,  0 },
	{ 16, 3925,  1 },
	{ 17, 4350,  0 },
	{ 18, 4800,  0 },
	{ 19, 5270,  0 },
	{ 20, 5760,  1 },
	{ 21, 6270,  0 },
	{ 22, 6900,  0 },
	{ 23, 7640,  0 },
	{ 24, 8040,  0 },
	{ 25, 8640,  1 },
	{ 26, 9265,  0 },
	{ 27, 9905,  0 },
	{ 28, 10575, 0 },
	{ 29, 12055, 0 },
	{ 30, 12895, 1 },
	{ 31, 13820, 0 },
	{ 32, 14825, 0 },
	{ 33, 15920, 0 },
	{ 34, 17055, 0 },
	{ 35, 18220, 1 },
	{ 36, 19760, 0 },
	{ 37, 21005, 0 },
	{ 38, 22290, 0 },
	{ 39, 23610, 0 },
	{ 40, 24965, 1 },
	{ 41, 26350, 0 },
	{ 42, 27775, 0 },
	{ 43, 31085, 0 },
	{ 44, 32775, 0 },
	{ 45, 34510, 1 },
	{ 46, 36290, 0 },
	{ 47, 38110, 0 },
	{ 48, 39975, 0 },
	{ 49, 41880, 0 }
} };
void Player::AddExp(int n) {
	m_exp += n;
	while (levelcaps[m_level - 1].cap >= m_exp) {
		m_exp -= levelcaps[m_level - 1].cap;
		m_level += 1;
	}
}
