#include "Entity.h"

std::istream& operator>> (std::istream& in, Position& position) {
	in >> position.x >> position.y;
	return in;
}

// <-- encapsulation -->
Position Entity::GetPosition() const { return m_pos; }
void Entity::SetPosition(Position position) { m_pos = position; }
char Entity::GetAppearance() const { return m_appearance; }
void Entity::SetAppearance(char appearance) { m_appearance = appearance; }