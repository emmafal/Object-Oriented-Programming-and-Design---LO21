#pragma once

#include "Piece.h"

class Fourmis : public Piece {
public:
	Fourmis(Couleur c) : Piece("Fourmis", TypePiece::Fourmis, c) {}
	virtual ~Fourmis() = default;
	std::set<Deplacement> getDeplacements(Position origine, const Plateau& p) const override;
	bool deplacementValide(const Plateau& p, const Deplacement& d) const;
};