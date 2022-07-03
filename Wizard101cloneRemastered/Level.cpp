#include "Level.h"

Level current_level;

std::vector<Npc> spawned_npcs;
std::vector<Gateway> spawned_gateways;
std::vector<Enemy> spawned_enemies;

std::istream& operator>> (std::istream& in, Level& level) {
	std::string str;
	std::wstring wstr;

	in >> level.m_level_size;
	in.ignore(1); // skip EOL

	// load NPCs data
	while (in.peek() != '<') {
		std::getline(in, str);
		wstr = widen(str);

		// example of a string to parse: A Headmaster Ambrose;5 8
		spawned_npcs.push_back(Npc(wstr[0], wstr.substr(2, wstr.find(';') - 2))); // Npc('A', "Headmaster Ambrose")
		wstr.erase(0, wstr.find(';') + 1); // 5 8
		spawned_npcs[spawned_npcs.size() - 1].SetPosition({
			std::stoi(wstr.substr(0, wstr.find(' '))), // 5
			std::stoi(wstr.substr(wstr.find(' ') + 1)) // 8
			});
	}
	std::getline(in, str); // skip to next line

	auto temp_location = locations_enum::None;
	auto temp_orientation = orientation_enum::None;
	Position temp_position;

	// load gateways data
	while (in.peek() != '<') {
		std::getline(in, str);
		wstr = widen(str);

		// example of a string to parse: H The Commons;3 5 5 0
		switch (wstr[0]) {
			case 'H':
				temp_orientation = orientation_enum::Horizontal;
				break;
			case 'V':
				temp_orientation = orientation_enum::Vertical;
				break;
		}
		for (const auto& n : map_wstr_location) {
			if (wstr.substr(2, wstr.find(';') - 2) == n.first) {
				temp_location = n.second; // locations_enum::The_Commons
				break;
			}
		}
		wstr.erase(0, wstr.find(';') + 1); // 3 5 5 0
		temp_position.x = std::stoi(wstr.substr(0, wstr.find(' ')));
		wstr.erase(0, wstr.find(' ') + 1); // 5 5 0
		temp_position.y = std::stoi(wstr.substr(0, wstr.find(' ')));
		wstr.erase(0, wstr.find(' ') + 1); // 5 0
		spawned_gateways.push_back(Gateway(temp_location, temp_position, temp_orientation));
		spawned_gateways[spawned_gateways.size() - 1].SetPosition({
			std::stoi(wstr.substr(0, wstr.find(' '))), // 5
			std::stoi(wstr.substr(wstr.find(' ') + 1)) // 0
			});
	}
	std::getline(in, str); // skip to next line

	int enemy_id = -1;
	Enemy temp_enemy;
	std::ifstream enemy_file;
	enemy_file.open("Data/enemies.txt");

	// load enemies data
	while (in.peek() != '<' && in.peek() != '\n') {
		in >> enemy_id;
		int i = 1;
		
		// skip to corresponding enemy's data
		for (; i < enemy_id; i++) {
			std::getline(enemy_file, str);
		}

		enemy_file >> temp_enemy;
		Position temp_pos;
		in >> temp_pos;
		temp_enemy.SetPosition(temp_pos);
		i++;
		spawned_enemies.push_back(temp_enemy);
	}
	enemy_file.close();
	if (enemy_id != -1)
		in.ignore(1); // ignore EOL character
	std::getline(in, str); // skip to next line

	// read the general layout of the level (wall or not wall; NPCs, gateways etc. placed in the level layout in file is for human readability)
	for (int i = 0; i < level.m_level_size.y; i++) {
		in >> str;
		wstr = widen(str);
		for (int j = 0; j < level.m_level_size.x; j++) {
			if (wstr[j] == level.m_barrier_char)
				level.m_cells.push_back({ cell_type_enum::Barrier, nullptr });
			else level.m_cells.push_back({ cell_type_enum::Empty, nullptr });
		}
	}

	// spawn NPCs (entity_ptr points inside the vector)
	for (int i = 0; i < spawned_npcs.size(); i++) {
		level.SpawnEntity(&spawned_npcs[i]);
	}

	// spawn gateways (entity_ptr points inside the vector)
	for (int i = 0; i < spawned_gateways.size(); i++) {
		level.SpawnEntity(&spawned_gateways[i]);
	}

	// spawn enemies (entity_ptr points inside the vector)
	for (int i = 0; i < spawned_enemies.size(); i++) {
		level.SpawnEntity(&spawned_enemies[i]);
	}

	return in;
}
void Level::SpawnEntity(Enemy* const entity_ptr) {
	m_cells[entity_ptr->GetPosition().to_index(m_level_size)] = {cell_type_enum::Enemy, entity_ptr};
}
void Level::SpawnEntity(Gateway* const entity_ptr) {
	m_cells[entity_ptr->GetPosition().to_index(m_level_size)] = { cell_type_enum::Gateway, entity_ptr };
}
void Level::SpawnEntity(Npc* const entity_ptr) {
	m_cells[entity_ptr->GetPosition().to_index(m_level_size)] = { cell_type_enum::Npc, entity_ptr };
}
void Level::SpawnEntity(Player* const entity_ptr) {
	m_cells[entity_ptr->GetPosition().to_index(m_level_size)] = { cell_type_enum::Player, entity_ptr };
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

		// position of current cell of player view translated to global coordinates
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

		// convert position to array index
		int j = gui_pos.to_index(m_level_size);

		Enemy* enemy_ptr;
		Gateway* gateway_ptr;
		Npc* npc_ptr;
		Player* player_ptr;
		// display appearance of current cell depending on what it is
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

LevelLayoutCell Level::GetCell(const Position position) const { return m_cells[position.to_index(m_level_size)]; }
void Level::ClearCell(const Position position) {
	auto cell = m_cells[position.to_index(m_level_size)];
	switch (cell.cell_type) {
		case cell_type_enum::Npc:
			//					ptr to vector		  cast to uint*				calculate index of current entity
			spawned_npcs.erase(spawned_npcs.begin() + std::uintptr_t(cell.entity_ptr - (Entity*)&spawned_npcs.front()) / sizeof(Npc));
			break;
		case cell_type_enum::Gateway:
			//							ptr to vector		  cast to uint*				calculate index of current entity
			spawned_gateways.erase(spawned_gateways.begin() + std::uintptr_t(cell.entity_ptr - (Entity*)&spawned_gateways.front()) / sizeof(Gateway));
			break;
		case cell_type_enum::Enemy:
			//							ptr to vector		  cast to uint*				calculate index of current entity
			spawned_enemies.erase(spawned_enemies.begin() + std::uintptr_t(cell.entity_ptr - (Entity*)&spawned_enemies.front()) / sizeof(Enemy));
			break;
	}
	m_cells[position.to_index(m_level_size)] = {cell_type_enum::Empty, nullptr};
}