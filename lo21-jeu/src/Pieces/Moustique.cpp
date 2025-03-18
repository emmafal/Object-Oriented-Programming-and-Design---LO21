#include "Moustique.h"
#include "Scarabee.h"
#include <algorithm>

std::set<Deplacement> Moustique::getDeplacements(Position origine, const Plateau& p) const
{
	if (!p.peutBouger(origine)) return std::set<Deplacement>();		// On vérifie que la pièce peut bouger

    std::set<Deplacement> moves;
    std::map<Position, Case> cases = p.getCases();
    Case current = cases.at(origine);

	if (current.getNbPieces() > 1) {
		Scarabee scarabee(getCouleur());
		return scarabee.getDeplacements(origine, p);
    }
    else {
		std::vector<Position> neighbors = current.getVoisins();
		for (Position posNeighbor : neighbors) {
			Case caseNeighbor = cases.at(posNeighbor);
			if (caseNeighbor.estOccupee() && caseNeighbor.getDernierePiece()->getType() != TypePiece::Moustique) {
				std::set<Deplacement> neighbor_moves = caseNeighbor.getDernierePiece()->getDeplacements(origine, p);
                moves.merge(neighbor_moves);
            }
        }
    }

    return moves;
}
