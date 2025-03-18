#include "IAFacile.h"
#include "PieceFactory.h"
#include <stdlib.h>

const Mouvement *IAFacile::choisirMouvement(Joueur &joueurIA, const Plateau &plateau, bool premierTour) const
{
	std::vector<const Piece *> piecesAllouees;
	const Deck &deck = joueurIA.getDeck();
	std::map<size_t, std::set<Placement>> placementsPotentiels;

	const Piece *piece = nullptr;
	size_t i = 0;
	for (Deck::effectif_iterator it = deck.begin(); it != deck.end(); ++it)
	{
		TypePiece type = (*it).first;
		size_t effectif = (*it).second;
		if (effectif > 0)
		{
			const Piece *piece = PieceFactory::construire(type, deck.getCouleur()); // D� � la structure du placement qui est cens� avoir le pointeur de la pi�ce, on doit allouer une pi�ce temporaire pour avoir les placements possibles
			piecesAllouees.push_back(piece);
			std::set<Placement> placements = piece->getPlacements(plateau, premierTour);
			placementsPotentiels.insert(std::pair(i++, placements));
		}
	}

	std::map<size_t, std::set<Deplacement>> deplacementsPotentiels;
	i = 0;
	for (Plateau::case_occupee_iterator it = plateau.begin(); it != plateau.end(); ++it)
	{
		const Case &c = (*it);
		const Piece *piece = c.getDernierePiece();
		if (piece->getCouleur() == deck.getCouleur())
		{
			std::set<Deplacement> deplacements = piece->getDeplacements(c.getPos(), plateau);
			if (deplacements.size() > 0)
			{
				deplacementsPotentiels.insert(std::pair(i++, deplacements));
			}
		}
	}

	if (placementsPotentiels.empty())
	{
		for (auto it = piecesAllouees.begin(); it != piecesAllouees.end(); ++it)
			delete (*it); // On l�b�re la m�moire allou�e aux pieces temporaires
		size_t i = rand() % deplacementsPotentiels.size();
		std::set<Deplacement> deplacementsChoisis = deplacementsPotentiels.at(i);
		i = rand() % deplacementsChoisis.size();
		for (const Deplacement &deplacement : deplacementsChoisis)
			if (i-- == 0)
				return new Deplacement(deplacement.getOrigine(), deplacement.getDest()); // On ne peut pas acc�der par index � un set, on utilise un smart pointer pour le polymorphisme
	}
	else
	{
		size_t i = 0;
		if (deplacementsPotentiels.empty())
			i = 0;
		else
			i = 1;
		i = rand() % (i + 1); // On choisit si on fait un placement ou un d�placement

		if (i == 0)
		{
			i = rand() % placementsPotentiels.size();
			std::set<Placement> placementsChoisis = placementsPotentiels.at(i);
			i = rand() % placementsChoisis.size();
			const Placement *placementSelectionne;
			for (const Placement &placement : placementsChoisis)
				if (i-- == 0)
					placementSelectionne = &placement;
			TypePiece type = placementSelectionne->getPiece()->getType();
			for (const Piece *piece : piecesAllouees)
				delete piece;
			joueurIA.selectionnerPieceDeck(type);
			return new Placement(joueurIA.getPieceSelectionnee(), placementSelectionne->getDest()); // On fait le placement d�finitif, en modifiant le deck de l'IA et en g�n�rant le pointeur d�finitif
		}
		else
		{
			size_t i = rand() % deplacementsPotentiels.size();
			std::set<Deplacement> deplacementsChoisis = deplacementsPotentiels.at(i);
			i = rand() % deplacementsChoisis.size();
			for (const Deplacement &deplacement : deplacementsChoisis)
				if (i-- == 0)
					return new Deplacement(deplacement.getOrigine(), deplacement.getDest());
		}
	}
	return nullptr;
}
