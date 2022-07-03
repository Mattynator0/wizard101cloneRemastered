#pragma once
#include <random>
#include <string>
#include <unordered_map>
#include <Windows.h>

enum class card_type_enum { None = 0, Spell, Treasure_Card, Item_Card };
enum class cell_type_enum { None = 0, Empty, Barrier, Enemy, Gateway, Npc, Player };
enum class item_type_enum { None = 0, Hat, Robe, Boots, Wand, Athame, Amulet, Ring, Deck };
enum class locations_enum { None = 0, The_Commons, Headmaster_Ambrose_Office, Ravenwood, Unicorn_Way };
enum class orientation_enum { None = 0, Horizontal, Vertical };
enum class school_enum { None = 0, Fire, Ice, Storm, Myth, Life, Death, Balance, Any }; // 'Any' is used for universal damage increase
enum class spell_deck_menu_enum { None = 0, Deck, Unlocked_Spells, Equipped_Treasure_Cards, Treasure_Cards, Item_Cards};
enum class spell_type_enum { None = 0, Damage, Healing, Ward, Charm, Global, Manipulation, Enchantment };

extern std::unordered_map<std::wstring, locations_enum> map_wstr_location;
extern std::unordered_map<std::wstring, school_enum> map_wstr_school;

template<typename _T>
_T RNG(_T lower, _T upper) {
	std::random_device rand_dev; // obtain a random number from hardware
	std::mt19937 generator(rand_dev()); // seed the generator
	std::uniform_int_distribution<_T> distr(lower, upper); // define the range
	return distr(generator);
}

// convert a wide Unicode string to a UTF8 string
std::string narrow(const std::wstring& wstr);

// convert a UTF8 string to a wide Unicode string
std::wstring widen(const std::string& str);