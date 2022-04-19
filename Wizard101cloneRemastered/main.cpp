#include "my_utility.h"

int main()
{
	std::cout.sync_with_stdio(false); // to be determined if it's necessary
	std::wcout.sync_with_stdio(false); // to be determined if it's necessary
	_setmode(_fileno(stdout), _O_U16TEXT);
	ShowConsoleCursor(false);

	LoadData();
	LoadLevel(locations_enum::Headmaster_Ambrose_Office);

	player.SetPosition({ 2, 2 });
	player.SetAppearance(*L"\u0040");
	current_level.SpawnEntity(&player);

	// Code only for testing
#if 1
	player.EquipItem(&items.at(7001));
	player.EquipItem(&items.at(3001));
	player.UnlockSpell(1);
	player.UnlockSpell(2);
	player.ResetHp();
#endif

	Gameloop();
}
// '!' - not fully implemented
// ----- ON LAUNCHING GAME -----
// load all essential data
	// spells, treasure cards, item cards
		// id
		// name
		// cost in pips and overall mana (cost -1 means it consumes all available pips, equivalent of cost X in Wizard101)
		// school
			/*
			* fire - high damage over time
			* ice - high health, low damage
			* storm - low health, high damage
			* myth - summoning minions, double-hit spells
			* life - healing
			* death - health drain
			* balance - universal
			*/
		// type
			/*
			* damage - deals damage to target(s) (in one hit or spread over time)
			* healing - heals target(s) (in one 'hit' or spread over time)
			* health drain (aka necromancy) - deals damage then returns half of it to source as healing (this healing isn't affected by global/charm/absorption spells)
			* wards (consumed after use):
				* shields are cast on self/allies; reduce incoming damage
				* traps are cast on opponents; increase incoming damage
				* absorption spells act like 'armor' - they absorb damage up to the amount specified in spell description and break when their durability reaches 0
			* charms (consumed after use; cast on self or single ally/opponent):
				* blades increase outgoing damage/heal or spell accuracy
				* debuffs decrease outgoing damage/heal or spell accuracy
			* global - global amplifiers that affect everyone and last for the duration of the battle (unless other global is cast, i.e. there can't be more than one global active at a time)
			* manipulation - summoning minions, reshuffling deck, giving pips to allies, prisms (convert school of incoming attack to the opposite), etc.
			* enchantment - can be used to 'enchant' a card with a boosted stat (generally increased damage or accuracy)
			*/
		// accuracy (in %)
		// description
	// items
		// clothing
			/*
			* hats
			* robes
			* boots
			*/
		// equipment
			/*
			* athame
			* ring
			* amulet
			* wand
			* deck
			*/
		// reagents
// current level
	//! enemies
	// NPCs
	// gateways (teleports to other levels)
//! create player
	// https://wizard101.fandom.com/wiki/Level_Chart
	// (in future) load player data
// choose and load level
	//! create enemies
	// spawn whatever should be spawned (player, NPCs, etc.)

// !!! STUFF BELOW THIS COMMENT HASN'T BEEN REVISED IN A LONG TIME !!!
// ----- ON EVERY PLAYER "ACTION" -----
// EXPLORATION:
	// draw 11x11 level grid around player (player is in the center)
	//! draw exploreUI
	//! ask for user input
		/* 
		* a - move left
		* b - backpack
		* c - character tab (basic info like name, stats, etc.)
		* d - move right
		* p - spell deck
		* q - quests
		* s - move down
		* w - move up
		* x - interact
		*/
//! BATTLE:
	// draw battleUI
		// display info about opponents and player
		// display cards currently in hand
	// 
//! BROWSING EQUIPMENT, SPELL DECK, ETC.
	//
	//