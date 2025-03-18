#include "Fourmis.h"
#include <queue>

bool Fourmis::deplacementValide(const Plateau& p, const Deplacement& d) const {
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

std::set<Deplacement> Fourmis::getDeplacements(Position origine, const Plateau& p) const
{
    if (!p.peutBouger(origine)) return std::set<Deplacement>();        // On v»rifie que la piÀce peut bouger

    std::set<Deplacement> moves;
    std::vector<Direction> dirs = Direction::getDirs();
    std::map<Position, Case> cases = p.getCases();

    std::set<Position> visited;       // Ensemble pour suivre les positions d»já visit»es
    std::queue<Position> toExplore;   // File pour g»rer les positions á explorer

    toExplore.push(origine); // Ajouter la position actuelle á explorer

    while (!toExplore.empty()) {
        Position current = toExplore.front();
        toExplore.pop(); // Extraire la premiÀre position de la file

        // Si on n'a pas encore visit» cette position
        if (visited.find(current) == visited.end()) {
            visited.insert(current); // Marquer comme visit»e

            int i = 0;
            // Parcourir tous les voisins de cette position
            for (auto it = dirs.begin(); it != dirs.end(); ++it, i++) {
                Position neighbor = current + *it;

                // V»rifier si la case voisine est libre, existe et n'a pas »t» visit»e
                if (cases.find(neighbor) != cases.end() &&
                    !cases.at(neighbor).estOccupee() &&
                    visited.find(neighbor) == visited.end())
                {
                    // V»rification des directions gauche et droite
                    Position gauche = current + dirs[(i - 1 + dirs.size()) % dirs.size()]; // Gestion circulaire
                    Position droite = current + dirs[(i + 1) % dirs.size()];
                    Deplacement dest(origine, neighbor);

                    bool glissement_possible = !(cases.find(gauche) != cases.end() && cases.at(gauche).estOccupee() &&
                        cases.find(droite) != cases.end() && cases.at(droite).estOccupee());

                    // Si glissement possible, ajouter neighbor á la liste des mouvements
                    if (glissement_possible && deplacementValide(p, dest)) {
                        moves.insert(Deplacement(origine, neighbor));
                        toExplore.push(neighbor); // Ajouter la position voisine á explorer
                    }
                }
            }
        }
    }
    return moves;
}
