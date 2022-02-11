#pragma once
#include "my_globals.h"
#include "Entity.h"

#include <unordered_map>

extern std::unordered_map<std::wstring, locations_enum> map_wstring_to_location;

// when player steps on a gateway, the level changes to 'm_destination'
class Gateway :
    public Entity
{
    // ----- functions -----
public:
    Gateway(locations_enum location, Position destination_spawn_pos, orientation_enum orientation);

    // <-- encapsulation -->
    virtual wchar_t GetAppearance();
    locations_enum GetDestination();
    Position GetDestinationSpawnPos();

    // ----- data -----
protected:
    static constexpr wchar_t m_gateway_horizontal_char = *L"\u2500";
    static constexpr wchar_t m_gateway_vertical_char = '|';
    locations_enum m_destination;
    Position m_destination_spawn_pos;
    orientation_enum m_orientation;
};

