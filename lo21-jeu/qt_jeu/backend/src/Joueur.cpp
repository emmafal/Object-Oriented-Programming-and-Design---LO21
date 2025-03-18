#include "Joueur.h"

std::ostream& operator<<(std::ostream& os, const Joueur& joueur)
{
	os << joueur.nom << ", " << joueur.couleur;
	return os;
}

void Joueur::selectionnerPieceDeck(TypePiece type)
{
	selectionnee = deck.prendrePiece(type);
}

void Joueur::finirSelection() {
    selectionnee = nullptr;
}
void Joueur::annulerSelection()
{
	if (selectionnee == nullptr) return;
	deck.reposerPiece(selectionnee->getType()); 
	selectionnee = nullptr;
}
