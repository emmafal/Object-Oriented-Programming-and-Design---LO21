#pragma once

#include "Piece.h"

class Moustique : public Piece {
public:
	Moustique(Couleur c) : Piece("Moustique", TypePiece::Moustique, c) {};
	virtual ~Moustique() = default;
    std::set<Deplacement> getDeplacements(Position origine, const Plateau& p) const override;
};

