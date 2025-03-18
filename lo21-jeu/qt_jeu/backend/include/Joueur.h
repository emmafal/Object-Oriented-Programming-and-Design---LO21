#pragma once
#include <string>

#include "Couleur.h"
#include "Deck.h"
#include "Piece.h"

enum class TypeJoueur {
	Humain,
	IA
};

class Joueur {
private:
	std::string nom;
	TypeJoueur type;
	Couleur couleur;
	Deck deck;
	const Piece* selectionnee;
public:
	Joueur(std::string nom, TypeJoueur type, Couleur couleur, Deck deck) : nom(nom), type(type), couleur(couleur), deck(deck), selectionnee(nullptr) {}
	Couleur getCouleur() const { return couleur; }
	const Deck& getDeck() const { return deck; }
	const std::string& getNom() const { return nom; }
	TypeJoueur getType() const { return type; }
	const Piece* getPieceSelectionnee() const { return selectionnee; }
	void selectionnerPieceDeck(TypePiece type);		// On prend une pièce du deck et on alloue de la mémoire pour cette pièce
    void finirSelection();
    void annulerSelection();						// On repose la pièce que l'on a sélectionnée dans le deck
	friend std::ostream& operator<<(std::ostream& os, const Joueur& joueur);
};
