#include "Level.h"

Level current_level;

std::vector<Npc> spawned_npcs;
std::vector<Gateway> spawned_gateways;
std::vector<Enemy> spawned_enemies;

std::istream& operator>> (std::istream& in, Level& level) {
	wchar_t temp_wchar;
	std::string temp_str;
	in >> level.m_level_size.x;
	in.ignore(1, ';');
	in >> level.m_level_size.y; // temp_char gets rid of ';' character separating data
	in.ignore(INT_MAX, '\n'); // get rid of EOL

	// load NPC data
	std::wstring wstr;
	while (true) {
		std::getline(in, temp_str);
		wstr = widen(temp_str);
		if (wstr == L"<") break;

		// example of a string to parse: A;Headmaster Ambrose;5;8
		temp_wchar = wstr[0];
		wstr.erase(0, wstr.find(';') + 1); // Headmaster Ambrose;5;8
		spawned_npcs.push_back(Npc(temp_wchar, wstr.substr(0, wstr.find(';')))); // Npc('A', "Headmaster Ambrose")
		wstr.erase(0, wstr.find(';') + 1); // 5;8
		spawned_npcs[spawned_npcs.size() - 1].SetPosition({
			std::stoi(wstr.substr(0, wstr.find(';'))), // 5
			std::stoi(wstr.substr(wstr.find(';') + 1)) // 8
			});
	}

	locations_enum temp_locations_enum = locations_enum::None;
	orientation_enum temp_orientation_enum = orientation_enum::None;
	Position temp_position;

	while (true) {
		std::getline(in, temp_str);
		wstr = widen(temp_str);
		if (wstr == L"<") break;

		// load in gateways
		// example of a string to parse: H;The Commons;3;5;5;0
		switch (wstr[0]) {
			case 'H':
				temp_orientation_enum = orientation_enum::Horizontal;
				break;
			case 'V':
				temp_orientation_enum = orientation_enum::Vertical;
				break;
		}
		wstr.erase(0, wstr.find(';') + 1); // The Commons;-1;-1;5;0
		for (const auto& n : map_wstring_to_location) {
			if (wstr.substr(0, wstr.find(';')) == n.first) {
				temp_locations_enum = n.second; // locations_enum::The_Commons
				break;
			}
		}
		wstr.erase(0, wstr.find(';') + 1); // 3;5;5;0
		temp_position.x = std::stoi(wstr.substr(0, wstr.find(';')));
		wstr.erase(0, wstr.find(';') + 1); // 5;5;0
		temp_position.y = std::stoi(wstr.substr(0, wstr.find(';')));
		wstr.erase(0, wstr.find(';') + 1); // 5;0
		spawned_gateways.push_back(Gateway(temp_locations_enum, temp_position, temp_orientation_enum));
		spawned_gateways[spawned_gateways.size() - 1].SetPosition({
			std::stoi(wstr.substr(0, wstr.find(';'))), // 5
			std::stoi(wstr.substr(wstr.find(';') + 1)) // 0
			});
	}

	// read the general layout of the level (wall or not wall)
	for (int i = 0; i < level.m_level_size.y; i++) {
		in >> temp_str;
		wstr = widen(temp_str);
		for (int j = 0; j < level.m_level_size.x; j++) {
			if (wstr[j] == level.m_barrier_char)
				level.m_cells.push_back({ cell_type_enum::Barrier, nullptr });
			else level.m_cells.push_back({ cell_type_enum::Empty, nullptr });
		}
	}

	// spawn NPCs (put pointers to them inside main vector)
	for (int i = 0; i < spawned_npcs.size(); i++) {
		level.SpawnEntity(&spawned_npcs[i]);
	}

	// spawn gateways (put pointers to them inside main vector)
	for (int i = 0; i < spawned_gateways.size(); i++) {
		level.SpawnEntity(&spawned_gateways[i]);
	}

	return in;
}
void Level::SpawnEntity(Enemy* const entity_ptr) {
	m_cells[entity_ptr->GetPosition().y * m_level_size.x + entity_ptr->GetPosition().x] = { cell_type_enum::Enemy, entity_ptr };
}
void Level::SpawnEntity(Gateway* const entity_ptr) {
	m_cells[entity_ptr->GetPosition().y * m_level_size.x + entity_ptr->GetPosition().x] = { cell_type_enum::Gateway, entity_ptr };
}
void Level::SpawnEntity(Npc* const entity_ptr) {
	m_cells[entity_ptr->GetPosition().y * m_level_size.x + entity_ptr->GetPosition().x] = { cell_type_enum::Npc, entity_ptr };
}
void Level::SpawnEntity(Player* const entity_ptr) {
	m_cells[entity_ptr->GetPosition().y * m_level_size.x + entity_ptr->GetPosition().x] = { cell_type_enum::Player, entity_ptr };
}

void Level::ClearLevel() {
	spawned_npcs.clear();
	spawned_gateways.clear();
	spawned_enemies.clear();
	player.SetPosition({ -1, -1 });

	m_cells.clear();
	m_level_size = { 0, 0 };
}
void Level::DrawLevel() {
	for (int i = 0; i < 121; i++) {
		if (i != 0 && i % 11 == 0)
			std::wcout << '\n';

		Position gui_pos = { player.GetPosition().x - 5 + i%11, player.GetPosition().y - 5 + i/11 };
		if (gui_pos.y < 0 || gui_pos.y >= current_level.m_level_size.y) {
			std::wcout << "           "; // 11x ' '
			i += 10;
			continue;
		}
		if (gui_pos.x < 0 || gui_pos.x >= current_level.m_level_size.x) {
			std::wcout << ' ';
			continue;
		}
		int j = gui_pos.y * m_level_size.x + gui_pos.x;

		Enemy* enemy_ptr;
		Gateway* gateway_ptr;
		Npc* npc_ptr;
		Player* player_ptr;
		switch (m_cells[j].cell_type) {
			case cell_type_enum::None:
				std::wcout << m_no_cell_char;
				break;
			case cell_type_enum::Empty:
				std::wcout << m_empty_cell_char;
				break;
			case cell_type_enum::Barrier:
				std::wcout << m_barrier_char;
				break;
			case cell_type_enum::Enemy:
				enemy_ptr = static_cast<Enemy*>(m_cells[j].entity_ptr);
				std::wcout << enemy_ptr->GetAppearance();
				break;
			case cell_type_enum::Gateway:
				gateway_ptr = static_cast<Gateway*>(m_cells[j].entity_ptr);
				std::wcout << gateway_ptr->GetAppearance();
				break;
			case cell_type_enum::Npc:
				npc_ptr = static_cast<Npc*>(m_cells[j].entity_ptr);
				std::wcout << npc_ptr->GetAppearance();
				break;
			case cell_type_enum::Player:
				player_ptr = static_cast<Player*>(m_cells[j].entity_ptr);
				std::wcout << player_ptr->GetAppearance();
				break;
		}
	}
}

LevelLayoutCell Level::GetCell(const Position position) const { return m_cells[position.y * m_level_size.x + position.x]; }
void Level::ClearCell(const Position position) {
	auto cell = m_cells[position.y * m_level_size.x + position.x];
	switch (cell.cell_type) {
		case cell_type_enum::Npc:
			spawned_npcs.erase(spawned_npcs.begin() + std::uintptr_t(cell.entity_ptr - (Entity*)&spawned_npcs.front()) / sizeof(Npc));
			break;
		case cell_type_enum::Gateway:
			spawned_gateways.erase(spawned_gateways.begin() + std::uintptr_t(cell.entity_ptr - (Entity*)&spawned_gateways.front()) / sizeof(Gateway));
			break;
		case cell_type_enum::Enemy:
			spawned_enemies.erase(spawned_enemies.begin() + std::uintptr_t(cell.entity_ptr - (Entity*)&spawned_enemies.front()) / sizeof(Enemy));
			break;
	}
	m_cells[position.y * m_level_size.x + position.x] = { cell_type_enum::Empty, nullptr };
}
void Level::AppendLayoutCell(const LevelLayoutCell cell) {
	m_cells.push_back(cell);
}