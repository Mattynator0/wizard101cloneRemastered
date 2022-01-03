#include "Gateway.h"

std::unordered_map<std::string, locations_enum> map_string_to_location = {
    { "Headmaster_Ambrose_Office", locations_enum::Headmaster_Ambrose_Office },
    { "The_Commons", locations_enum::The_Commons },
    { "Ravenwood", locations_enum::Ravenwood },
    { "Unicorn_Way", locations_enum::Unicorn_Way }
};

// ----- functions -----
Gateway::Gateway(locations_enum location, orientation_enum orientation) : m_destination(location), m_orientation(orientation) {}

// <-- encapsulation -->
char Gateway::Get_appearance() {
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
locations_enum Gateway::Get_destination() { return m_destination; }