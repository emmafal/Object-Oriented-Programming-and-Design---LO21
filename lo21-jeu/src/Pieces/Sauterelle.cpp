#include "Sauterelle.h"

std::set<Deplacement> Sauterelle::getDeplacements(Position origine, const Plateau& p) const
{
	if (!p.peutBouger(origine)) return std::set<Deplacement>();		// On vérifie que la pièce peut bouger

    std::set<Deplacement> moves;
    std::vector<Direction> dirs = Direction::getDirs();
    std::map<Position, Case> cases = p.getCases();

    for (auto it = dirs.begin(); it != dirs.end(); ++it) {
        Position temp = origine + *it;
        if (cases.at(temp).estOccupee()) {
            Position dest = temp;
            while (cases.at(dest).estOccupee()) dest = dest + *it;
            moves.insert(Deplacement(origine, dest));
        }
    }

    return moves;
}
