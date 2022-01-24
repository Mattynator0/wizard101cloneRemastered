#include "Gateway.h"

std::unordered_map<std::string, locations_enum> map_string_to_location = {
    { "Headmaster Ambrose Office", locations_enum::Headmaster_Ambrose_Office },
    { "The Commons", locations_enum::The_Commons },
    { "Ravenwood", locations_enum::Ravenwood },
    { "Unicorn Way", locations_enum::Unicorn_Way }
};

// ----- functions -----
Gateway::Gateway(locations_enum location, Position destination_spawn_pos, orientation_enum orientation)
    : m_destination(location), m_destination_spawn_pos(destination_spawn_pos), m_orientation(orientation) {}

// <-- encapsulation -->
char Gateway::GetAppearance() {
    switch (m_orientation) {
        case orientation_enum::Horizontal:
            return gateway_horizontal_char;
            break;
        case orientation_enum::Vertical:
            return gateway_vertical_char;
            break;
        default:
            return ' ';
    }
}
locations_enum Gateway::GetDestination() { return m_destination; }
Position Gateway::GetDestinationSpawnPos() { return m_destination_spawn_pos; }