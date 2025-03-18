#pragma once

#include "Piece.h"

class Araignee : public Piece {
public:
	Araignee(Couleur c) : Piece("Araignee", TypePiece::Araignee, c) {}
	virtual ~Araignee() = default;
	bool deplacementValide(const Plateau& p, const Deplacement& d) const;
    std::set<Deplacement> getDeplacements(Position origine, const Plateau& p) const override;
};

