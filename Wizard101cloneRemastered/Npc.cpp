#include "NPC.h"

// ----- functions -----
Npc::Npc(char appearance, std::string name) : m_appearance(appearance), m_name(name) {}

// <-- encapsulation -->
std::string Npc::Get_name() { return m_name; }
char Npc::Get_appearance() { return m_appearance; }
