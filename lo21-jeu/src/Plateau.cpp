#include <set>
#include <algorithm>
#include "Plateau.h"
#include "Piece.h"
#include "PieceFactory.h"
#include <fstream>
#include <stdexcept>
#include <sstream>


Plateau::Plateau()
{
	Position pos_initiale = Position(0, 0);
	cases.insert(std::pair(pos_initiale, Case(pos_initiale)));
}

void Plateau::liberer()
{
	for (auto it = piecesPosees.begin(); it != piecesPosees.end(); ++it) delete (*it);	// On définit un destructeur manuel pour pouvoir utiliser des copies facilement sans supprimer les pièces
}

void Plateau::placerPiece(const Piece * piece, Position dest)
{
	Case& caseDest = (*(cases.insert(std::pair(dest, Case(dest)))).first).second;
	
	for (Position voisin : caseDest.getVoisins()) cases.insert(std::pair(voisin, Case(voisin)));

	caseDest.poserPiece(piece);
	piecesPosees.push_back(piece);
}

void Plateau::deplacerPiece(Position origine, Position dest)
{
	Case& caseOrigine = cases.at(origine);
	Case& caseDest = (*(cases.insert(std::pair(dest, Case(dest)))).first).second;

	for (Position voisin : caseDest.getVoisins()) cases.insert(std::pair(voisin, Case(voisin)));

	const Piece* p = caseOrigine.getDernierePiece();
	caseOrigine.retirerPiece();
	caseDest.poserPiece(p);
}

void Plateau::supprimerPiece(Position dest)
{
	auto it = cases.find(dest);
	if (it != cases.end()) {
		Case& caseDest = (*it).second;
		const Piece* piece = caseDest.getDernierePiece();
		caseDest.retirerPiece();
		piecesPosees.erase(std::find(piecesPosees.begin(), piecesPosees.end(), piece));
		delete piece;
	}
}

bool Plateau::estRuche() const
{
	for (auto it = cases.begin(); it != cases.end(); ++it) {		// On cherche une case avec une pièce de laquelle partir
		if ((*it).second.estOccupee()) {
			const Case& debut = (*it).second;
			std::set<Position> visitees;											// On initialise un set qui sera utilisé pour le parcours
			return parcourirCasesOccupees(debut, visitees) == getNbPieces();		// On passe en référence la case et le set, on compare le résultat avec le vrai résultat
		}
	}

	return getNbPieces() == 0;	// Si on n'en a pas trouvé, on vérifie qu'il n'y a bien aucune pièce sur le plateau
}

bool Plateau::peutBouger(Position origine) const
{
	if (cases.find(origine) == cases.end()) return false;
	Plateau copie = *this;
	copie.cases.at(origine).retirerPiece();
	copie.piecesPosees.pop_back();		// On retire une pièce de la liste des pièces posées pour que getNbPieces() renvoie le nombre de pièces - 1. La pièce retirée n'est pas importante.
	return copie.estRuche();
}

bool Plateau::peutPoser(Position origine, Couleur couleur, bool premierTour) const
{
	if (cases.find(origine) == cases.end() || cases.at(origine).estOccupee()) return false;

	std::vector<Position> voisins = cases.at(origine).getVoisins();

	bool connecte = false;

	if (premierTour && getNbPieces() == 0) return true;

	for (auto it = voisins.begin(); it != voisins.end(); ++it) {
		auto toCheck = cases.find(*it);
		if (toCheck != cases.end() && (*toCheck).second.estOccupee()) {
			if (premierTour) return true;
			if ((*toCheck).second.getDernierePiece()->getCouleur() != couleur) return false;
			connecte = true;
		}
	}
	return connecte;
}

bool Plateau::deplacementsDisponibles(Couleur couleur) const
{
	for (case_occupee_iterator it = begin(); it != end(); ++it) {
		const Case& c = (*it);
		const Piece* piece = c.getDernierePiece();
		if (piece->getCouleur() == couleur && piece->getDeplacements(c.getPos(), *this).size() > 0) return true;
	}
	return false;
}

bool Plateau::placementsDisponibles(const Deck& deck, bool premierTour) const
{
	for (Deck::effectif_iterator it = deck.begin(); it != deck.end(); ++it) {
		TypePiece type = (*it).first;
		size_t effectif = (*it).second;
		if (effectif > 0) {
			const Piece* piece = PieceFactory::construire(type, deck.getCouleur());
			std::set<Placement> placements = piece->getPlacements(*this, premierTour);
			delete piece;
			if (placements.size() > 0) return true;
		}
	}
	return false;
}


size_t Plateau::parcourirCasesOccupees(const Case& origine, std::set<Position>& visitees) const {	// Fonction récursive qui parcourt les cases et renvoie le nombre de pièces qu'elle a trouvé
	std::vector<Position> voisins = origine.getVoisins();
	size_t total = origine.getNbPieces();

	visitees.insert(origine.getPos());

	for (Position voisin : voisins) {
		if (!visitees.contains(voisin) and cases.at(voisin).estOccupee()) {		// Sachant que des cases sont initialisées à chaque fois que l'on pose ou déplace une pièce, il est impossible qu'une case ne soit pas initialisée en allant de pièce en pièce
			total += parcourirCasesOccupees(cases.at(voisin), visitees);
		}
	}

	return total;
}

std::ostream& operator<<(std::ostream& os, const Plateau& p)
{
	return os;
}

Plateau::case_occupee_iterator::case_occupee_iterator(const std::map<Position, Case>& cases, const std::map<Position, Case>::const_iterator& it): current(it), cases(cases)
{
	while (current != cases.end() and !(*current).second.estOccupee()) current++;
}

Plateau::case_occupee_iterator& Plateau::case_occupee_iterator::operator++()
{
	while (++current != cases.end()) if ((*current).second.estOccupee()) break;
	return *this;
}

void Plateau::save(std::ofstream& outFile) const {
    if (!outFile.is_open()) {
        throw std::runtime_error("Erreur d'ouverture du fichier pour la sauvegarde.");
    }

    for (case_occupee_iterator it = begin(); it != end(); ++it) {
        const Case& caseData = *it;
        const Position& pos = caseData.getPos();

        for (Case::piece_iterator pieceIt = caseData.begin(); pieceIt != caseData.end(); ++pieceIt) {
            const Piece* piece = *pieceIt;
            outFile << pos.getQ() << " " << pos.getR() << " "
                    << static_cast<unsigned int>(piece->getCouleur()) << " "
                    << static_cast<unsigned int>(piece->getType()) << "\n";
        }
    }

    outFile << "END_PLATEAU\n";
}

void Plateau::load(std::ifstream& inFile) {
    if (!inFile.is_open()) {
        throw std::runtime_error("Erreur d'ouverture du fichier pour le chargement.");
    }

    cases.clear();
    std::string line;

    while (std::getline(inFile, line)) {
        if (line == "END_PLATEAU") break;

        std::istringstream iss(line);
        int q, r;
        unsigned int couleur, type;

        if (!(iss >> q >> r >> type >> couleur)) {
            throw std::runtime_error("Erreur de format : ligne invalide - " + line);
        }

        Position pos(q, r);
        try {
            const Piece* piece = PieceFactory::construire(static_cast<TypePiece>(type), static_cast<Couleur>(couleur));
            placerPiece(piece, pos);
            //std::cout << " coordonees : (" << q << " , " << r << ")" << " piece : " << type << "\n";
        } catch (const std::exception& e) {
            throw std::runtime_error("Erreur lors de la reconstruction des pièces : " + std::string(e.what()));
        }
    }
}