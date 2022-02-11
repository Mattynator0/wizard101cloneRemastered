#include "NPC.h"

// ----- functions -----
Npc::Npc(wchar_t appearance, std::wstring name) : m_appearance(appearance), m_name(name) {}

// <-- encapsulation -->
std::wstring Npc::GetName() const { return m_name; }
wchar_t Npc::GetAppearance() const { return m_appearance; }
