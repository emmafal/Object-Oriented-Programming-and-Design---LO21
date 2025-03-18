#pragma once

#include "Piece.h"

class Coccinelle : public Piece {
public:
    Coccinelle(Couleur c) : Piece("Coccinelle", TypePiece::Coccinelle, c) {};
    virtual ~Coccinelle() = default;
    std::set<Deplacement> getDeplacements(Position origine, const Plateau& p) const override;
};
