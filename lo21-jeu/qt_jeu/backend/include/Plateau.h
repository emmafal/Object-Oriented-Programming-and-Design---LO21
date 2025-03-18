#pragma once
#include <map>
#include <set>

#include "Case.h"
#include "Position.h"
#include "Couleur.h"
#include "Deck.h"



class Piece;

class Plateau {
private:
	std::map<Position, Case> cases;
	std::vector<const Piece*> piecesPosees;

	size_t parcourirCasesOccupees(const Case& origine, std::set<Position>& visitees) const;
public:
	Plateau();
	void liberer();

	const std::map<Position, Case>& getCases() const { return cases; }
	size_t getNbPieces() const { return piecesPosees.size(); }

	void placerPiece(const Piece * piece, Position dest);
	void deplacerPiece(Position origine, Position dest);
	void supprimerPiece(Position dest);	// N'est pas censée être utilisée autre que pour le retour en arrière 

	bool estRuche() const;
	bool peutBouger(Position origine) const;
	bool peutPoser(Position origine, Couleur couleur, bool premierTour = false) const;
	
	bool deplacementsDisponibles(Couleur couleur) const;	// Vérifie si un joueur peut bouger au moins une pièce sur le plateau
	bool placementsDisponibles(const Deck& deck, bool premierTour) const;

	class case_occupee_iterator {
	private:
		const std::map<Position, Case>& cases;
		std::map<Position, Case>::const_iterator current;
		case_occupee_iterator(const std::map<Position, Case>& cases, const std::map<Position, Case>::const_iterator& it);
	public:
		case_occupee_iterator& operator++();
		const Case& operator*() const { return (*current).second; }
		bool operator==(const case_occupee_iterator& other) const { return current == other.current; }
		friend class Plateau;
	};

	case_occupee_iterator begin() const { return case_occupee_iterator(cases, cases.begin()); }
	case_occupee_iterator end() const { return case_occupee_iterator(cases, cases.end()); }
};


