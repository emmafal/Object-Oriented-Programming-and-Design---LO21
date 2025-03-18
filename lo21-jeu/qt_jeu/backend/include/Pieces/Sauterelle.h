#pragma once

#include "Piece.h"

class Sauterelle : public Piece {
public:
	Sauterelle(Couleur c) : Piece("Sauterelle", TypePiece::Sauterelle, c) {}
	virtual ~Sauterelle() = default;
    std::set<Deplacement> getDeplacements(Position origine, const Plateau& p) const override;
};
