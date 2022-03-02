#include "Gateway.h"

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