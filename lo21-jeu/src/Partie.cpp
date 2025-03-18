#include <stdlib.h>
#include "Partie.h"
#include "Interface.h"
#include "ReineAbeille.h"
#include <fstream>
#include <stdexcept>

Joueur& Partie::getJoueurActuel()
{
	if (joueur1.getCouleur() == tour) return joueur1;
	else return joueur2;
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


void Partie::lancer()
{
	nbTours++;
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

void Partie::abandonner()
{
    if (fin == TypeFin::Aucune){
        Joueur* gagnant;
        if (joueur1.getCouleur() == getJoueurActuel().getCouleur()) gagnant = &joueur2;
        else gagnant = &joueur1;
        interface.finirPartie(*this, *gagnant);
    }
    
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
	if (historiqueMouvements.size() < 2 || sauvegardes.size() < 2) return;

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
	os << "Nombre de tours : " << p.nbTours << "\n";
	return os;
}

void Partie::saveToFile(const std::string& fileName) const {
    std::ofstream outFile(fileName);
    if (!outFile.is_open()) {
        throw std::runtime_error("Erreur lors de l'ouverture du fichier pour la sauvegarde.");
    }
    std::cout << "Fichier de sauvegarde : " << fileName << "\n";
    Memento memento = creerMemento();
    memento.save(outFile);
    outFile.close();
}


void Partie::loadFromFile(const std::string& fileName) {
    std::ifstream inFile(fileName);
    if (!inFile.is_open()) {
        throw std::runtime_error("Erreur lors de l'ouverture du fichier pour le chargement.");
    }

    try {
        Memento memento(*this);
        memento.load(inFile);
        memento.restaurer(*this);

        // Reset game state variables if needed
        updateFin(); // Ensure the game end state is recalculated
        if (fin != TypeFin::Aucune) {
            std::cout << "La partie chargee est deja terminee. Voulez-vous la visualiser ou demarrer une nouvelle partie ?\n";
            return;
        }

        std::cout << *this;
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Erreur lors du chargement de la partie : ") + e.what());
    }

    inFile.close();
}




void Partie::restaurerPartie() {
    if (!sauvegardes.empty()) {
        Memento memento = sauvegardes.top();
        sauvegardes.pop();
        memento.restaurer(*this);
        std::cout << "Partie restaurée." << std::endl;
    } else {
        std::cout << "Aucune sauvegarde disponible." << std::endl;
    }
}