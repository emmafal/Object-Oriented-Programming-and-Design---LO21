#pragma once

#include <exception>

#include "TypeInsecte.h"
#include "Couleur.h"

#include "Piece.h"
#include "Moustique.h"
#include "ReineAbeille.h"
#include "Scarabee.h"
#include "Sauterelle.h"
#include "Araignee.h"
#include "Fourmis.h"
#include "Coccinelle.h"

class PieceFactory {
private:
public:
	static const Piece* construire(TypePiece type, Couleur couleur) {	// Permet de construire une pi�ce � partir de son type, � modifier quand on ajoute de nouvelles pi�ces
		switch (type) {
		case TypePiece::ReineAbeille:
			return new ReineAbeille(couleur);
		case TypePiece::Moustique:
			return new Moustique(couleur);
		case TypePiece::Sauterelle:
			return new Sauterelle(couleur);
		case TypePiece::Scarabee:
			return new Scarabee(couleur);
		case TypePiece::Araignee:
			return new Araignee(couleur);
		case TypePiece::Fourmis:
			return new Fourmis(couleur);
		case TypePiece::Coccinelle:
			return new Coccinelle(couleur);
		};
		throw std::runtime_error("Insecte inconnu de la factory ou pas implemente");
	}
	static std::vector<TypePiece> getExtensions() {	// Le but est de faire le moins de d�placements possibles lorsque l'on veut ajouter de nouvelles extensions
		std::vector<TypePiece> extensions{
			TypePiece::Moustique,
			TypePiece::Coccinelle
		};
		return extensions;
	}
	
	static std::string getNomByType(TypePiece type) {	// Pas tr�s efficace, mais �vite de devoir faire un map qui associe le nom au type et qu'il faudra changer en plus de la factory lors de l'ajout d'autres insectes
		const Piece* temp = construire(type, Couleur::Blanc);
		std::string nom = temp->getNom();
		delete temp;
		return nom;
	}
};