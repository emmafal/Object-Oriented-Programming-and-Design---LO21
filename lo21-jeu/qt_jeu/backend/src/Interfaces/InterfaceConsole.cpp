#include <iostream>
#include <iomanip>
#include <format>
#include <random>
#include "InterfaceConsole.h"
#include "Partie.h"
#include "PieceFactory.h"
#include "AsciiBoard.h"
#include "HexPrinter.h"
#include "IAFacile.h"

Partie InterfaceConsole::configurerPartie() {
	std::cout << "****** CONFIGURATION PARTIE ******\n\n";

	std::string nomJoueur1;
	std::string nomJoueur2;
	int nbRetoursArriere;
	size_t joueurIa;

	std::cout << "Nom du joueur 1: ";
	std::cin >> nomJoueur1;

	std::cout << "\nNom du joueur 2: ";
	std::cin >> nomJoueur2;

	std::cout << "Jouer contre une IA (0: non, 1: oui) :";

	while (!(std::cin >> joueurIa) || joueurIa < 0 || joueurIa > 1) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "(non valide)\n";
		std::cout << "\n\nJouer contre une IA (0: non, 1: oui) :";
	}

	std::cout << "\n\nNombre de retours en arriere: ";
	while (!(std::cin >> nbRetoursArriere) || nbRetoursArriere < 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "(non valide)\n";
		std::cout << "\n\nNombre de retours en arriere: ";
	}

	Couleur couleurJoueur1;
	Couleur couleurJoueur2;

	std::random_device rd;
	std::uniform_int_distribution dist(0, 1);		// Meilleur random, pas forcément nécessaire, on détermine qui commence en premier

	if (dist(rd) == 0) {
		couleurJoueur1 = Couleur::Blanc;
		couleurJoueur2 = Couleur::Noir;
	}
	else {
		couleurJoueur1 = Couleur::Noir;
		couleurJoueur2 = Couleur::Blanc;
	}

	Deck deckJoueur1 = Deck::deckStandard(couleurJoueur1);
	Deck deckJoueur2 = Deck::deckStandard(couleurJoueur2);

	std::vector<TypePiece> extensions = PieceFactory::getExtensions();

	std::cout << "Ajouter des extensions (o/n):";

	char choix;

	while (!(std::cin >> choix) || (choix != 'o' && choix != 'n')) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "(non valide)\n";
		std::cout << "Ajouter des extensions (o/n): ";
	}

	std::cout << "\n\n";

	if (choix == 'o') {
		while (!extensions.empty()) {
			size_t choixExtension;
			size_t i = 0;
			std::cout << "0. Sortir\n\n";
			for (auto it = extensions.begin(); it != extensions.end(); ++it) {
				std::cout << ++i << ". " << PieceFactory::getNomByType(*it) << "\n";
			}
			while (!(std::cin >> choixExtension) || choixExtension < 0 || choixExtension > i) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Veuillez entre une option valide !\n";
			}

			if (choixExtension == 0) break;

			deckJoueur1.ajouterExtension(extensions.at(choixExtension - 1), 1);
			deckJoueur2.ajouterExtension(extensions.at(choixExtension - 1), 1);
			extensions.erase(extensions.begin() + choixExtension - 1);

			std::cout << "\n\n";
		}
	}

	Joueur joueur1(nomJoueur1, TypeJoueur::Humain, couleurJoueur1, deckJoueur1);

	TypeJoueur type;
	if (joueurIa == 1) type = TypeJoueur::IA;
	else type = TypeJoueur::Humain;

	Joueur joueur2(nomJoueur2, type, couleurJoueur2, deckJoueur2);

	IA* ia = new IAFacile();			// Une partie a toujours un attribut IA qui permet de générer un mouvement, même s'il n'y a pas de joueur IA
	return Partie(joueur1, joueur2, *this, nbRetoursArriere, *ia);
}

void InterfaceConsole::afficherPlateau(const Plateau &p) const {
	std::cout << "*** PLATEAU ***\n\n";

	if (p.getCases().size() == 0) {
        std::cout << "Aucune case sur le plateau, plateau possiblement errone" << "\n";
		return;
	}

	if (p.getNbPieces() == 0) {
		const Case& premiereCase = (*p.getCases().begin()).second;
		std::cout << premiereCase.getPos() << "\n\n";
		return;
	}

	HexPrinter printer = HexPrinter();

	const Position& positionPremiereCase = (*p.begin()).getPos();	// Position de la première case occupée
	int minQ = positionPremiereCase.getQ();
	int minR = positionPremiereCase.getR();
	int maxQ = minQ;
	int maxR = minR;

	for (Plateau::case_occupee_iterator it = p.begin(); it != p.end(); ++it) {	// On cherche les coordonnées minimales et maximales qui déterminent la taille du plateau
		const Case& c = (*it);
		const Position& positionCase = c.getPos();
		if (positionCase.getQ() < minQ) minQ = positionCase.getQ();
		if (positionCase.getQ() > maxQ) maxQ = positionCase.getQ();
		if (positionCase.getR() < minR) minR = positionCase.getR();
		if (positionCase.getR() > maxR) maxR = positionCase.getR();
	}

	int maxQBoard = maxQ - minQ;	// Taille Q maximale
	int maxRBoard = maxR - minR;	// Taille R maximale

	std::cout << "Q: " << maxQBoard << ", R: " << maxRBoard << "\n\n";

	AsciiBoard board = AsciiBoard(0, maxQBoard, 0, maxRBoard, printer);

	std::vector<Case> casesPiecesSuperposees;		// Les cases qui ont plusieurs pièces seront affichées différemment

	for (Plateau::case_occupee_iterator it = p.begin(); it != p.end(); ++it) {
		const Case& caseActuelle = (*it);
		const Position& posActuelle = caseActuelle.getPos();

		if (caseActuelle.getNbPieces() > 1) casesPiecesSuperposees.push_back(caseActuelle);

		std::stringstream sq;
		std::stringstream sr;

		sq << std::setw(3) << std::setfill(' ') << posActuelle.getQ();		// La chaîne de caractère doit faire exactement 7 caractères
		sr << std::setw(3) << std::setfill(' ') << posActuelle.getR();

		std::string posString = std::format("{},{}", sq.str(), sr.str());
		std::string pieceString = std::string(2, ' ') + '-' + caseActuelle.getDernierePiece()->getNom().at(0) + '-' + std::string(2, ' ');

		int actualQ = posActuelle.getQ() - minQ;		// L'afficheur ne prend pas les coordonnées négatives, on fait donc un offset
		int actualR = posActuelle.getR() - minR;

		char fillerChar;
		if (caseActuelle.getDernierePiece()->getCouleur() == Couleur::Blanc) fillerChar = ' ';
		else fillerChar = '/';				// Pour les cases noires, on les remplit de '/'
		board.addHex(posString, pieceString, fillerChar, actualQ, actualR);		// On ajoute l'hexagone
	}
	std::cout << board.prettyPrint(false) << "\n\n";		// On affiche le plateau, sans cadre

	for (auto it = casesPiecesSuperposees.begin(); it != casesPiecesSuperposees.end(); ++it ) {
		const Case& c = (*it);
		size_t i = 0;

		std::cout << c.getPos() << ": \n";
		for (Case::reverse_piece_iterator it2 = c.rbegin(); it2 != c.rend(); ++it2, i++) {		// On affiche pour les cases où les pièces sont superposées une liste des pièces présentes sur la case
			std::cout << std::string(i, '\t') << **it2 << "\n";
		}
		std::cout << "\n";
	}

	std::cout << "\n\n";
}

void InterfaceConsole::choisirDeplacement(Partie& partie, Joueur& joueur) const {
	std::cout << "****** CHOIX DEPLACEMENT ******\n\n";
	const Plateau& plateau = partie.getPlateau();

	if (plateau.getNbPieces() == 0) {
		std::cout << "Aucune piece a deplacer" << "\n";
		std::cout << "Retour au menu...\n\n";
		choisirAction(partie, joueur);
		return;
	}

	std::vector<Case> piecesAccessibles;

	size_t i = 0;
	for (Plateau::case_occupee_iterator it = plateau.begin(); it != plateau.end(); ++it) {
		const Case& c = (*it);
		const Piece* p = c.getDernierePiece();
		if (p->getCouleur() == joueur.getCouleur()) {
			std::cout << ++i << ". " << *p << " : " << c.getPos() << "\n";
			piecesAccessibles.push_back(c);
		}
	}
	
	std::cout << "\n";

	if (i == 0) {
		std::cout << "Vous ne pouvez deplacer aucune piece" << "\n";
		std::cout << "Retour au menu..." << "\n\n";
		choisirAction(partie, joueur);
		return;
	}

	size_t choix;
	while (!(std::cin >> choix) || choix < 1 || choix > i) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Veuillez entrer une option valide !\n";
	}

	std::cout << "\n";

	const Case& caseSelectionnee = piecesAccessibles[choix - 1];
	std::set<Deplacement> deplacements = caseSelectionnee.getDernierePiece()->getDeplacements(caseSelectionnee.getPos(), partie.getPlateau());

	if (deplacements.empty()) {
		std::cout << "Aucun deplacement possible pour cette piece" << "\n";
		std::cout << "Retour a la selection de piece..." << "\n\n";
		choisirDeplacement(partie, joueur);
		return;
	}

	i = 0;
	for (auto it = deplacements.begin(); it != deplacements.end(); ++it) {
		std::cout << ++i << ". " << *it << "\n";
	}

	std::cout << "\n";

	while (!(std::cin >> choix) || choix < 1 || choix > i) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Veuillez entrer une option valide !\n";
	}

	std::cout << "\n";

	for (auto it = deplacements.begin(); it != deplacements.end(); ++it) {
		if (choix - 1 == 0) partie.jouerTour(&(*it));
		choix--;
	}

}

void InterfaceConsole::choisirPlacement(Partie& partie, Joueur& joueur) const {
	std::cout << "****** CHOIX PLACEMENT ******\n\n";
	Deck deck = joueur.getDeck();
	if (deck.getNbPiecesRestantes() == 0) {
		std::cout << "Aucune piece restante a poser" << "\n";
		std::cout << "Retour au menu..." << "\n\n";
		choisirAction(partie, joueur);
		return;
	}

	std::vector<TypePiece> options;
	std::vector<std::string> toShow;

	size_t i = 0;


	for (Deck::effectif_iterator it = deck.begin(); it != deck.end(); ++it) {
		TypePiece type = (*it).first;
		size_t effectif = (*it).second;
		if (effectif > 0) {
			const Piece* temp = PieceFactory::construire(type, deck.getCouleur());
			if (temp->getPlacements(partie.getPlateau(), partie.getNbTours() == 1).size() != 0) {
				std::string strPiece = std::format("{}. {} ({})\n", ++i, temp->getNom(), effectif);
				options.push_back(type);
				toShow.push_back(strPiece);
				delete temp;
			}
		}
	}

	std::cout << "Veuillez choisir la piece a poser : " << "\n\n";

	for (auto it = toShow.begin(); it != toShow.end(); ++it) std::cout << (*it);

	std::cout << "\n";

	size_t choix;

	while (!(std::cin >> choix) || choix < 1 || choix > i) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Veuillez entrer une option valide !\n";
	}
	

	joueur.selectionnerPieceDeck(options[choix-1]);
	const Piece* pieceChoisie = joueur.getPieceSelectionnee();

	std::set<Placement> placements = pieceChoisie->getPlacements(partie.getPlateau(), partie.getNbTours() == 1);

	if (placements.empty()) {
		std::cout << "Aucun placement disponible pour cette piece" << "\n";
		std::cout << "Retour a la selection de piece..." << "\n\n";
		choisirPlacement(partie, joueur);
		return;
	}

	std::cout << "\nVeuillez choisir le placement que vous voulez effectuer : " << "\n\n";

	i = 0;
	for (const Placement& placement : placements) {
		std::cout << ++i << ". " << placement << "\n";
	}

	std::cout << "\n";

	while (!(std::cin >> choix) || choix < 1 || choix > i) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Veuillez entrer une option valide !\n";
	}

	for (auto it = placements.begin(); it != placements.end(); ++it) {
		if (choix - 1 == 0) {
			partie.jouerTour(&(*it));
			return;
		}
		choix--;
	}

}

void InterfaceConsole::choisirAction(Partie& partie, Joueur& joueur) const
{
	bool placementsPossible = partie.getPlateau().placementsDisponibles(joueur.getDeck(), partie.getNbTours() == 1);
	bool deplacementsPossible = partie.getPlateau().deplacementsDisponibles(joueur.getCouleur());

	if (!placementsPossible and !deplacementsPossible) {
		std::cout << "Aucune action possible, votre tour saute " << joueur.getNom() << "\n\n";
		partie.passerTour();
	}

	if (joueur.getType() == TypeJoueur::IA) {
		const Mouvement* mouv = partie.getIA().choisirMouvement(joueur, partie.getPlateau(), partie.getNbTours() == 1);
		partie.jouerTour(mouv);
		return;
	}

	std::cout << "****** CHOIX ACTION ******\n\n";
	afficherPlateau(partie.getPlateau());
	std::cout << "\n\nC'est a " << joueur.getNom() << " (" << joueur.getCouleur() << ")" << " de jouer !\n\n\n\n";

	std::cout << "*** DECK ***\n\n";


	const Deck& deck = joueur.getDeck();
	std::cout << deck << "\n";

	if (partie.getNbTours() == 4 && !deck.reinePosee()) {
		std::cout << "Votre etes oblige de poser votre reine" << "\n\n";
		joueur.selectionnerPieceDeck(TypePiece::ReineAbeille);
		const Piece* reine = joueur.getPieceSelectionnee();
		std::set<Placement> placements = reine->getPlacements(partie.getPlateau(), false);

		size_t i = 0;
		for (const Placement& placement : placements) {
			std::cout << ++i << ". " << placement << "\n";
		}

		std::cout << "\n";

		size_t choix;
		while (!(std::cin >> choix) || choix < 1 || choix > i) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Veuillez entrer une option valide !\n";
		}

		for (auto it = placements.begin(); it != placements.end(); ++it) {
			if (choix - 1 == 0) partie.jouerTour(&(*it));
			choix--;
		}
	}

	std::cout << "Voulez-vous poser une piece ou en deplacer une ?" << "\n1: Poser une piece" << "\n2: Deplacer piece" << "\n3: Revenir en arriere\n\n";
	size_t option;
	while (!(std::cin >> option) || (option < 1 && option > 3)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Veuillez entrer une option valide !\n";
	}
	
	switch (option) {
	case 1:
		choisirPlacement(partie, joueur);
		break;
	case 2:
        choisirDeplacement(partie, joueur);
        break;
    case 3:
        partie.retourArriere();
        choisirAction(partie, joueur);
        break;
	}

}

void InterfaceConsole::lancerPartie(Partie& partie) const
{
	std::cout << "****** LANCEMENT DE LA PARTIE ******\n\n";
	std::cout << partie << "\n\n";
}

void InterfaceConsole::finirPartie(Partie& partie, Joueur& gagnant) const
{
	std::cout << "****** FIN DE LA PARTIE ******\n\n";
	std::cout << "Partie terminée !\n";
	if (partie.getFin() == TypeFin::Egalite) {
		std::cout << "Égalité parfaite !";
	}
	else {
		std::cout << "Victoire de " << gagnant.getNom() << " (" << gagnant.getCouleur() << ")\n\n";
	}
	return;
}


