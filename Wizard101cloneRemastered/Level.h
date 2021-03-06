#pragma once
#include "my_globals.h"
#include "Enemy.h"
#include "Gateway.h"
#include "Npc.h"
#include "Player.h"

#include <array>
#include <vector>

extern std::vector<Npc> spawned_npcs;
extern std::vector<Gateway> spawned_gateways;
extern std::vector<Enemy> spawned_enemies;

// TODO consider renaming it to something more intuitive than "level layout cell"
struct LevelLayoutCell {
	cell_type_enum cell_type = cell_type_enum::Empty;
	Entity* entity_ptr = nullptr;
};

class Level
{
	// ----- functions -----
public:
	friend std::istream& operator>> (std::istream& in, Level& level);
	void SpawnEntity(Enemy* const entity_ptr);
	void SpawnEntity(Gateway* const entity_ptr);
	void SpawnEntity(Npc* const entity_ptr);
	void SpawnEntity(Player* const entity_ptr);

	void ClearLevel();
	void DrawLevel();

	// <-- encapsulation -->
	LevelLayoutCell GetCell(const Position position) const;
	void ClearCell(const Position position);
	void AppendLayoutCell(const LevelLayoutCell cell);

	// ----- data -----
public:

protected:
	static constexpr wchar_t m_no_cell_char = ' '; // empty cell inaccessible by player
	static constexpr wchar_t m_empty_cell_char = '.'; // empty cell accessible by player
	static constexpr wchar_t m_barrier_char = '#';
	Position m_level_size;
	std::vector<LevelLayoutCell> m_cells;
};

std::istream& operator>> (std::istream& in, Level& level);

extern Level current_level;