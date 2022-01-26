#include "Gateway.h"

std::unordered_map<std::wstring, locations_enum> map_wstring_to_location = {
    { L"Headmaster Ambrose Office", locations_enum::Headmaster_Ambrose_Office },
    { L"The Commons", locations_enum::The_Commons },
    { L"Ravenwood", locations_enum::Ravenwood },
    { L"Unicorn Way", locations_enum::Unicorn_Way }
};

// ----- functions -----
Gateway::Gateway(locations_enum location, Position destination_spawn_pos, orientation_enum orientation)
    : m_destination(location), m_destination_spawn_pos(destination_spawn_pos), m_orientation(orientation) {}

// <-- encapsulation -->
wchar_t Gateway::GetAppearance() {
    switch (m_orientation) {
        case orientation_enum::Horizontal:
            return m_gateway_horizontal_char;
            break;
        case orientation_enum::Vertical:
            return m_gateway_vertical_char;
            break;
        default:
            return ' ';
    }
}
locations_enum Gateway::GetDestination() { return m_destination; }
Position Gateway::GetDestinationSpawnPos() { return m_destination_spawn_pos; }