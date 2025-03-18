#include "Scarabee.h"


bool Scarabee::deplacementValide(const Plateau& p, const Deplacement& d) const {
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
            // Condition spéciale : vérifier si seules deux cases sont occupées
            size_t nbCasesOccupees = 0;
            for (const auto& pair : cases) {
                if (pair.second.estOccupee()) nbCasesOccupees++;
            }
            if (nbCasesOccupees == 2 && caseDest.estOccupee()) return true; // Le scarabée va sur la seule autre case occupée
        }
    }
    return false;
}

std::set<Deplacement> Scarabee::getDeplacements(Position origine, const Plateau& p) const
{
	if (!p.peutBouger(origine)) return std::set<Deplacement>();		// On vérifie que la pièce peut bouger

    std::set<Deplacement> moves;
    std::vector<Direction> dirs = Direction::getDirs();
    std::map<Position, Case> cases = p.getCases();

    int i = 0;
    for (auto it = dirs.begin(); it != dirs.end(); ++it, i++)
    {
        Position gauche = origine + dirs[(i - 1 + dirs.size()) % dirs.size()]; // Gestion circulaire
        Position droite = origine + dirs[(i + 1) % dirs.size()];
        Position dest = origine + *it;
        
        bool position_valide = !((cases.at(gauche).estOccupee() && cases.at(droite).estOccupee()) &&
                                 (cases.at(gauche).getNbPieces() > cases.at(dest).getNbPieces()
                                  && cases.at(droite).getNbPieces() > cases.at(dest).getNbPieces()
                                  && cases.at(gauche).getNbPieces() > cases.at(origine).getNbPieces()-1
                                  && cases.at(droite).getNbPieces() > cases.at(origine).getNbPieces()-1));
        
        Deplacement d(origine, dest);
        if (position_valide && deplacementValide(p, d)) moves.insert(d);
    }

    return moves;
}

