#include "Couleur.h"

std::ostream& operator<<(std::ostream& os, Couleur c) {
	if (c == Couleur::Blanc) os << "Blanc";
	else os << "Noir";
	return os;
}