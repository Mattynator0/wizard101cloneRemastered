#include "NPC.h"

// ----- functions -----
Npc::Npc(char appearance, std::string name) : m_appearance(appearance), m_name(name) {}

// <-- encapsulation -->
std::string Npc::GetName() { return m_name; }
char Npc::GetAppearance() { return m_appearance; }
