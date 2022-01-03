#pragma once
#include "my_globals.h"
#include "Entity.h"

#include <unordered_map>
#include <string>

extern std::unordered_map<std::string, locations_enum> map_string_to_location;

class Gateway :
    public Entity
{
    // ----- functions -----
public:
    Gateway(locations_enum location, orientation_enum orientation);

    // <-- encapsulation -->
    virtual char Get_appearance();
    locations_enum Get_destination();

    // ----- data -----
protected:
    static constexpr char gateway_horizontal_char = '-';
    static constexpr char gateway_vertical_char = '|';
    locations_enum m_destination;
    orientation_enum m_orientation;
};

