#pragma once
#include <string>
#include <unordered_map>
#include <Windows.h>

enum class cell_type_enum { None = 0, Empty, Barrier, Enemy, Gateway, Npc, Player };
enum class item_type_enum { None = 0, Hat, Robe, Boots, Wand, Athame, Amulet, Ring, Deck };
enum class locations_enum { None = 0, The_Commons, Headmaster_Ambrose_Office, Ravenwood, Unicorn_Way };
enum class orientation_enum { None = 0, Horizontal, Vertical };
enum class school_enum { None = 0, Fire, Ice, Storm, Myth, Life, Death, Balance };
enum class spell_type_enum { None = 0, Damage, Healing, Necromancy, Ward, Charm, Global, Manipulation, Enchantment };
enum class card_type_enum { None = 0, Spell, Item_Card, Treasure_Card };
enum class spell_deck_menu_enum { None = 0, Deck, Unlocked_Spells, Item_Cards, Equipped_Treasure_Cards, Treasure_Cards };

std::unordered_map<std::wstring, locations_enum> map_wstring_to_location = {
    { L"Headmaster Ambrose Office", locations_enum::Headmaster_Ambrose_Office },
    { L"The Commons", locations_enum::The_Commons },
    { L"Ravenwood", locations_enum::Ravenwood },
    { L"Unicorn Way", locations_enum::Unicorn_Way }
};
std::unordered_map<std::wstring, school_enum> map_wstring_to_school = {
    { L"Fire", school_enum::Fire },
    { L"fire", school_enum::Fire },
    { L"Ice", school_enum::Ice },
    { L"ice", school_enum::Ice },
    { L"Storm", school_enum::Storm },
    { L"storm", school_enum::Storm },
    { L"Myth", school_enum::Myth },
    { L"myth", school_enum::Myth },
    { L"Life", school_enum::Life },
    { L"life", school_enum::Life },
    { L"Death", school_enum::Death },
    { L"death", school_enum::Death },
    { L"Balance", school_enum::Balance },
    { L"balance", school_enum::Balance },
};

// convert a wide Unicode string to a UTF8 string
std::string narrow(const std::wstring& wstr);

// convert a UTF8 string to a wide Unicode String
std::wstring widen(const std::string& str);