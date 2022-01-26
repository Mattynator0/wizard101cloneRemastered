#pragma once
#include <string>
#include <Windows.h>

enum class cell_type_enum { None = 0, Empty, Barrier, Enemy, Gateway, Npc, Player };
enum class locations_enum { None = 0, The_Commons, Headmaster_Ambrose_Office, Ravenwood, Unicorn_Way };
enum class school_enum { None = 0, Fire, Ice, Storm, Myth, Life, Death, Balance };
enum class spell_type_enum { None = 0, Damage, Healing, Necromancy, Ward, Charm, Global, Manipulation, Enchantment };
enum class orientation_enum { None = 0, Horizontal, Vertical };

// convert a wide Unicode string to a UTF8 string
std::string narrow(const std::wstring& wstr);

// convert a UTF8 string to a wide Unicode String
std::wstring widen(const std::string& str);