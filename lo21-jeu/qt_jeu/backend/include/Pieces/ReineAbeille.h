#pragma once
#include "Piece.h"

class ReineAbeille : public Piece {
public:
    ReineAbeille(Couleur c) : Piece("Reine Abeille", TypePiece::ReineAbeille, c) {}
    virtual ~ReineAbeille() = default;

    std::set<Deplacement> getDeplacements(Position origine, const Plateau &p) const override;
    bool estEntouree(Position origine, const Plateau &p) const;
    bool deplacementValide(const Plateau& p, const Deplacement& d) const;
};

