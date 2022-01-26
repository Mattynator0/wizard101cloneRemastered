#include "my_utility.h"

#include <iostream>

int main()
{
	//std::wcout.sync_with_stdio(false); // to be determined if it's necessary
	_setmode(_fileno(stdout), _O_U16TEXT);

	LoadData();
	LoadLevel(locations_enum::Headmaster_Ambrose_Office);

	player.SetPosition({ 2, 2 });
	player.SetAppearance(*L"\u0040");
	current_level.SpawnEntity(&player);

	Gameloop();
}
// ! - not fully implemented
// ----- ON LAUNCHING GAME -----
// load all essential data
	//! spells
		// id
		// name
		// cost in pips and overall mana (cost -1 means it consumes all available pips)
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
				* absorption spells act like 'armor' - they absorb damage up to the amount specified in spell description; they don't protect against health draining spells
			* charms (consumed after use; cast on self or single ally/opponent):
				* blades increase outgoing damage/heal or spell accuracy
				* debuffs decrease outgoing damage/heal or spell accuracy
			* global - global amplifiers that affect everyone and last for the duration of the battle (unless other global is cast, i.e. there can't be more than one global active at a time)
			* manipulation - summoning minions, reshuffling deck, giving pips to allies, prisms (convert school of incoming attack to the opposite), etc.
			* enchantment - can be used to 'enchant' a card and convert it to a treasure card with a boosted stat (generally increased damage or accuracy)
			*/
		// accuracy (in %)
		// description (string to be parsed with a special function)
			// first char is spell type: {d,h,n,w,c,g,m,e}
			// TODO: make use of ascii values to encode data in the string
			// https://www.asciitable.com
	//! enemies
	//! items
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
	// NPCs
//! create player
	// https://wizard101.fandom.com/wiki/Level_Chart
	// (in future) load player data
//! choose and load level
	// create enemies
	// spawn whatever should be spawned (player, NPCs, etc.)

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