#pragma once
#include "Entity.h"
#include "Item.h"
#include "Spell.h"

#include <algorithm>
#include <array>
#include <vector>

struct LevelCap;
struct Deck {
	int max_spell_count = 0;
	int max_copies = 0;
	std::vector<int> spells;

	void AddSpell(int id);
	void RemoveSpell(int id);
	int GetSpellCount(int id);
	void Clear();
};

class Player : public Entity
{
// ----- functions -----
public:
	Player(const std::wstring& name, const school_enum school);

	// <-- encapsulation -->
	std::wstring& GetName();
	school_enum GetSchool() const;
	int GetLevel() const;
	int GetExp() const;
	void AddExp(const int n);
	std::vector<int> GetUnlockedSpells() const;
	void UnlockSpell(int id);
	std::vector<int> GetItemsInBackpack() const;
	void AddItem(int id);
	std::array<Item*, 8> GetEquippedItems() const;
	void EquipItem(Item* item_ptr);
	void ClearStats();
	void UpdateStats();

	int GetHp() const;
	int GetMaxhp() const;
	int GetMana() const;
	int GetMaxmana() const;
	int GetPowerpipChance() const;
	int GetTrainingPoints() const;
	int GetGold() const;
	std::array<int, 7> GetDamageRaw() const;
	std::array<int, 7> GetDamagePercentage() const;
	std::array<int, 7> GetResistanceRaw() const;
	std::array<int, 7> ResistancePercentage() const;
	std::array<int, 7> GetAccuracyRaw() const;
	std::array<int, 7> GetAccuracyPercentage() const;
	int GetHealingIn() const;
	int GetHealingOut() const;
	Deck GetDeck() const;
	std::vector<int> GetItemCards() const;

	Player(Player&) = delete;
	void operator=(const Player&) = delete;

// ----- data -----
protected:
	std::wstring m_name;
	school_enum m_school;
	int m_level = 1, m_exp = 0;

	std::vector<int> m_unlocked_spells;
	std::vector<int> m_items_in_backpack; // max 100
	std::array<Item*, 8> m_equipped_items;

	int m_hp, m_maxhp;
	int m_mana, m_maxmana;
	int m_powerpip_chance;
	int m_training_points = 0;
	int m_gold = 0;
	std::array<int, 7> m_damage_raw;
	std::array<int, 7> m_damage_percentage;
	std::array<int, 7> m_resistance_raw;
	std::array<int, 7> m_resistance_percentage;
	std::array<int, 7> m_accuracy_raw;
	std::array<int, 7> m_accuracy_percentage;
	int m_healing_in, m_healing_out;

	Deck m_deck;
	std::vector<int> m_item_cards;
};

extern Player player;