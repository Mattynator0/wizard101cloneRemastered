#include "Level.h"

std::vector<Npc> spawned_npcs;
std::vector<Gateway> spawned_gateways;
std::vector<Enemy> spawned_enemies;

std::istream& operator>> (std::istream& in, Level& level) {
	in >> level.level_size_x >> level.level_size_y;
	int level_size = level.level_size_x * level.level_size_y;

	// load npc data
	std::string str;
	char temp_char;
	while (true) {
		std::getline(in, str);
		if (str == "") continue;
		if (str[0] == '<') break;

		// example of a string to parse: A Headmaster_Ambrose 5 8
		temp_char = str[0];
		str.erase(0, str.find(' ') + 1); // Headmaster_Ambrose 5 8
		spawned_npcs.push_back(Npc(temp_char, str.substr(0, str.find(' ')))); // (A, Headmaster_Ambrose)
		str.erase(0, str.find(' ') + 1); // 5 8
		spawned_npcs[spawned_npcs.size() - 1].Set_position({
			std::stoi(str.substr(0, str.find(' '))), // 5
			std::stoi(str.substr(str.find(' ') + 1, str.find('\n'))) // 8
			});
	}

	locations_enum temp_locations_enum = locations_enum::None;
	orientation_enum temp_orientation_enum = orientation_enum::None;
	while (true) {
		std::getline(in, str);
		if (str[0] == '<')
			break;

		// example of a string to parse: H The_Commons 5 0
		switch (str[0]) {
			case 'H':
				temp_orientation_enum = orientation_enum::Horizontal;
				break;
			case 'V':
				temp_orientation_enum = orientation_enum::Vertical;
				break;
		}
		str.erase(0, str.find(' ') + 1); // The_Commons 5 0
		for (const auto& n : map_string_to_location) {
			if (str.substr(0, str.find(' ')) == n.first)
				temp_locations_enum = n.second; // locations_enum::The_Commons
		}
		spawned_gateways.push_back(Gateway(temp_locations_enum, temp_orientation_enum));
		str.erase(0, str.find(' ') + 1); // 5 0
		spawned_gateways[spawned_gateways.size() - 1].Set_position({
			std::stoi(str.substr(0, str.find(' '))), // 5
			std::stoi(str.substr(str.find(' ') + 1, str.find('\n'))) // 0
			});
	}

	for (int i = 0; i < level_size; i++) {
		in >> temp_char;
		if (temp_char == level.barrier_char)
			level.m_cells.push_back({ cell_type_enum::Barrier, nullptr });
		else level.m_cells.push_back({ cell_type_enum::Empty, nullptr });
	}

	for (int i = 0; i < spawned_npcs.size(); i++) {
		level.SpawnEntity(&spawned_npcs[i]);
	}

	for (int i = 0; i < spawned_gateways.size(); i++) {
		level.SpawnEntity(&spawned_gateways[i]);
	}

	return in;
}
void Level::SpawnEntity(Enemy* const entity_ptr) {
	m_cells[entity_ptr->Get_position().y * level_size_x + entity_ptr->Get_position().x] = { cell_type_enum::Enemy, entity_ptr };
}
void Level::SpawnEntity(Gateway* const entity_ptr) {
	m_cells[entity_ptr->Get_position().y * level_size_x + entity_ptr->Get_position().x] = { cell_type_enum::Gateway, entity_ptr };
}
void Level::SpawnEntity(Npc* const entity_ptr) {
	m_cells[entity_ptr->Get_position().y * level_size_x + entity_ptr->Get_position().x] = { cell_type_enum::Npc, entity_ptr };
}
void Level::SpawnEntity(Player* const entity_ptr) {
	m_cells[entity_ptr->Get_position().y * level_size_x + entity_ptr->Get_position().x] = { cell_type_enum::Player, entity_ptr };
}
void Level::DrawLevel() {
	for (int i = 0; i < level_size_x * level_size_y; i++) {
		if (i != 0 && i % level_size_x == 0)
			std::cout << '\n';

		Enemy* enemy_ptr;
		Gateway* gateway_ptr;
		Npc* npc_ptr;
		Player* player_ptr;
		switch (m_cells[i].cell_type) {
			case cell_type_enum::Empty:
				std::cout << empty_cell_char;
				break;
			case cell_type_enum::Barrier:
				std::cout << barrier_char;
				break;
			case cell_type_enum::Enemy:
				enemy_ptr = static_cast<Enemy*>(m_cells[i].entity_ptr);
				std::cout << enemy_ptr->Get_appearance();
				break;
			case cell_type_enum::Gateway:
				gateway_ptr = static_cast<Gateway*>(m_cells[i].entity_ptr);
				std::cout << gateway_ptr->Get_appearance();
				break;
			case cell_type_enum::Npc:
				npc_ptr = static_cast<Npc*>(m_cells[i].entity_ptr);
				std::cout << npc_ptr->Get_appearance();
				break;
			case cell_type_enum::Player:
				player_ptr = static_cast<Player*>(m_cells[i].entity_ptr);
				std::cout << player_ptr->Get_appearance();
				break;
		}
	}
}

LevelLayoutCell Level::GetCell(const Position position) { return m_cells[position.y * level_size_x + position.x]; }
void Level::AppendLayoutCell(const LevelLayoutCell cell) {
	m_cells.push_back(cell);
}