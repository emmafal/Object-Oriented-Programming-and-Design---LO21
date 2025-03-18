#pragma once

#include <vector>
#include <iostream>
#include <map>

#include "TypeInsecte.h"
#include "Couleur.h"

class Piece;

class Deck {
private:
	std::map<TypePiece, size_t> effectifPieces;
	Couleur couleur;
public:
	Deck(std::map<TypePiece, size_t> effectif, Couleur c);
	static Deck deckStandard(Couleur c);

	void ajouterExtension(TypePiece piece, size_t effectif);

	size_t getNbPiecesRestantes() const;
	Couleur getCouleur() const { return couleur; }
	bool reinePosee() const { return effectifPieces.at(TypePiece::ReineAbeille) == 0; }


	const std::map<TypePiece, size_t>& getEffectifs() const { return effectifPieces; }

	const Piece* prendrePiece(TypePiece type);
	void reposerPiece(TypePiece type);

	friend std::ostream& operator<<(std::ostream& os, const Deck& deck);

	class effectif_iterator {
	private:
		std::map<TypePiece, size_t>::const_iterator current;
		effectif_iterator(std::map<TypePiece, size_t>::const_iterator it) : current(it) {}
	public:
		const std::pair<const TypePiece, size_t>& operator*() const { return *current; }
		effectif_iterator& operator++() { current++; return *this; };
		bool operator==(const effectif_iterator& other) const { return current == other.current; }
		friend class Deck;
	};

	effectif_iterator begin() const { return effectif_iterator(effectifPieces.begin()); };
	effectif_iterator end() const { return effectif_iterator(effectifPieces.end()); };
    
    void save(std::ofstream& outFile) const;
    void load(std::ifstream& inFile);
};