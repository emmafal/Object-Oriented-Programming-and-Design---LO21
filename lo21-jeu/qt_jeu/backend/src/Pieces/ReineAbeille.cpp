#include "ReineAbeille.h"

bool ReineAbeille::estEntouree(Position origine, const Plateau &p) const {
	const std::map<Position, Case>& cases = p.getCases();
	std::vector<Position> voisins = cases.at(origine).getVoisins();
	for (Position voisin : voisins) if (!cases.at(voisin).estOccupee()) return false;
	return true;
}


bool ReineAbeille::deplacementValide(const Plateau& p, const Deplacement& d) const {
    const std::map<Position, Case>& cases = p.getCases();
    const Case& caseDest = cases.at(d.getDest());
    const Case& caseOrigine = cases.at(d.getOrigine());
    
    for (const Position& voisin : caseDest.getVoisins()) {
        auto it = cases.find(voisin);
        if (it != cases.end() && (*it).second.estOccupee())
        {
            const Case& caseVoisine = (*it).second;
            if (caseVoisine.getPos() != caseOrigine.getPos()) return true;
            if (caseVoisine.getNbPieces() - 1 > 0) return true;
        }
    }
    return false;
}

std::set<Deplacement> ReineAbeille::getDeplacements(Position origine, const Plateau &p) const
{
	if (!p.peutBouger(origine)) return std::set<Deplacement>();		// On vérifie que la pièce peut bouger

	std::set<Deplacement> moves;
	std::vector<Direction> dirs = Direction::getDirs();
	const std::map<Position, Case>& cases = p.getCases();

	int i = 0;

	for (auto it = dirs.begin(); it != dirs.end(); ++it, i++) {
		Position gauche;
		Position droite;
		Position dest = origine + *it;

		if (i - 1 < 0) {
			gauche = origine + *(dirs.end() - 1);
			droite = origine + *(it + 1);
		}
		else if (i + 1 >= dirs.size()) {
			gauche = origine + *(it - 1);
			droite = origine + *(dirs.begin());
		}
		else {
			gauche = origine + *(it - 1);
			droite = origine + *(it + 1);
		}

		bool pos_valide = !(cases.at(gauche).estOccupee() and cases.at(droite).estOccupee()) and !cases.at(origine + *it).estOccupee();

        Deplacement d(origine, dest);
        if (pos_valide && deplacementValide(p, d)) moves.insert(d);
	}

	return moves;
}

