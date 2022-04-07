#include "Entity.h"

Position::Position() {}
Position::Position(int x, int y) : x(x), y(y) {}
int Position::to_index(Position size) const {
	return y * size.x + x;
}
Position Position::operator+(Position other) {
	return { x + other.x, y + other.y };
}

std::istream& operator>> (std::istream& in, Position& position) {
	in >> position.x >> position.y;
	return in;
}

// <-- encapsulation -->
Position Entity::GetPosition() const { return m_pos; }
void Entity::SetPosition(Position position) { m_pos = position; }
wchar_t Entity::GetAppearance() const { return m_appearance; }
void Entity::SetAppearance(char app) { m_appearance = app; }