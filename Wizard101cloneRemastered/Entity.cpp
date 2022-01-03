#include "Entity.h"

// <-- encapsulation -->
Position Entity::Get_position() const { return m_pos; }
void Entity::Set_position(Position position) { m_pos = position; }
char Entity::Get_appearance() const { return m_appearance; }
void Entity::Set_appearance(char appearance) { m_appearance = appearance; }