#include <stdlib.h>
#include "Partie.h"
#include "Interface.h"
#include "ReineAbeille.h"
#include "PieceFactory.h"

Joueur& Partie::getJoueurActuel()
{
	if (joueur1.getCouleur() == tour) return joueur1;
	else return joueur2;
}

Joueur& Partie::getJoueur1()
{
    return joueur1;
}

Joueur& Partie::getJoueur2()
{
    return joueur2;
}

void Partie::changerCote()
{
	if (tour == Couleur::Blanc) tour = Couleur::Noir;
	else {
		tour = Couleur::Blanc;
		nbTours++;
	}
}

void Partie::updateFin()
{
	const std::map<Position, Case>& cases = plateau.getCases();
	for (std::pair<Position, Case> paire : cases) if (paire.second.estOccupee()) {
		const Piece* premierePiece = (*paire.second.begin());
		if (premierePiece->getType() == TypePiece::ReineAbeille && static_cast<const ReineAbeille*>(premierePiece)->estEntouree(paire.first, plateau)) {
			if (fin == TypeFin::Aucune) {
				if (premierePiece->getCouleur() == Couleur::Noir) fin = TypeFin::Blanc;
				else fin = TypeFin::Noir;
			}
			else if (fin == TypeFin::Blanc || fin == TypeFin::Noir) {
				fin = TypeFin::Egalite;
				break;
			}

		}
	}
}

bool Partie::actionPossible(const Joueur& joueur) const {
	const Deck& deck = joueur.getDeck();
	for (auto it = deck.begin(); it != deck.end(); ++it) {
		TypePiece type = (*it).first;
		size_t effectif = (*it).second;
		if (effectif > 0) {
			const Piece* piece = PieceFactory::construire(type, deck.getCouleur());
            std::set<Placement> placements = piece->getPlacements(plateau, nbTours == 0);
			delete piece;
			if (!placements.empty()) return true;
		}
	}
	
	for (Plateau::case_occupee_iterator it = plateau.begin(); it != plateau.end(); ++it) {
		const Case& c = (*it);
		if (c.getDernierePiece()->getCouleur() == joueur.getCouleur()) {
            std::set<Deplacement> deplacements = c.getDernierePiece()->getDeplacements(c.getPos(), plateau);
			if (!deplacements.empty()) return true;
		}
	}

	return false;
}


void Partie::lancer()
{
	interface.lancerPartie(*this);
	sauvegarderPartie();
	interface.choisirAction(*this, getJoueurActuel());
}

void Partie::finir()
{
	Joueur* gagnant;
	if (fin == TypeFin::Blanc && joueur1.getCouleur() == Couleur::Blanc) gagnant = &joueur1;
	else if (fin == TypeFin::Noir && joueur1.getCouleur() == Couleur::Noir) gagnant = &joueur1;
	else gagnant = &joueur2;
	interface.finirPartie(*this, *gagnant);
}

void Partie::jouerTour(const Mouvement* mouvement)
{
	mouvement->executer(plateau);		
	updateFin();						// On vérifie si le jeu est fini
	if (fin == TypeFin::Aucune) {
		changerCote();							// S'il n'est pas fini, le tour passe au jour adverse
		historiqueMouvements.push(mouvement);	// On sauvegarde chaque mouvement qui est exécuté
		sauvegarderPartie();
		interface.choisirAction(*this, getJoueurActuel());
	}
	else {
		finir();
	}
}

void Partie::passerTour()
{
	changerCote();
	interface.choisirAction(*this, getJoueurActuel());
}

Memento Partie::creerMemento() const {
    return Memento(*this);
}

void Partie::restaurerEtat(const Plateau& p, const Joueur& j1, const Joueur& j2, size_t nbt, Couleur t, TypeFin f, std::stack<const Mouvement*> historique) {	// On ne restaure pas le nombre de retours en arrière, sinon on pourrait revenir infiniment en arrière
    plateau = p;
    joueur1 = j1;
    joueur2 = j2;
    tour = t;
    nbTours = nbt;
    fin = f;
	historiqueMouvements = historique;
}

void Partie::sauvegarderPartie() {
    sauvegardes.push(creerMemento());
}

void Partie::retourArriere() {
    if (historiqueMouvements.size() < 2 || sauvegardes.size() < 2 || nbRetoursArriere < 1) return;

	historiqueMouvements.top()->annuler(plateau);		// On annule un possible placement pour libérer la mémoire de la pièce

	historiqueMouvements.pop();		// On supprime supprime les deux derniers mouvements
	sauvegardes.pop();

	historiqueMouvements.top()->annuler(plateau);

	sauvegardes.pop();
	historiqueMouvements.pop();

	sauvegardes.top().restaurer(*this);		// On restaure la sauvegarde précédente

	nbRetoursArriere--;
}

std::ostream& operator<<(std::ostream& os, const Partie& p)
{
	os << "Joueur 1 : " << p.joueur1 << "\n";
	os << "Joueur 2 : " << p.joueur2 << "\n\n";
	os << "Tour : " << p.tour << "\n";
	os << "Nombre de tours : " << p.nbTours;
	return os;
}
