#include "Position.h"

bool Position::operator<(Position other) const	// Défini de manière arbitraire, important à conserver pour les map et les set
{
    if (q < other.q) return true;
    if (q == other.q) {
        if (r < other.r) return true;
        else return false;
    }
    else return false;
}

bool Position::operator==(Position other) const
{
    return q == other.q && r == other.r;
}

Position Position::operator+(Direction dir) const
{
    return Position(q + dir.getQ(), r + dir.getR());
}

std::ostream& operator<<(std::ostream& os, Position p)
{
	os << "(" << p.getQ() << ", " << p.getR() << ")";
    return os;
}
