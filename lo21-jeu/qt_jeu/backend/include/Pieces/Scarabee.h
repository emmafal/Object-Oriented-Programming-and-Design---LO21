#pragma once

#include "Piece.h"

class Scarabee: public Piece {
public:
	Scarabee(Couleur c) : Piece("Scarabee", TypePiece::Scarabee, c) {};
	virtual ~Scarabee() = default;
    std::set<Deplacement> getDeplacements(Position origine, const Plateau& p) const override;
	bool deplacementValide(const Plateau& p, const Deplacement& d) const;
};

