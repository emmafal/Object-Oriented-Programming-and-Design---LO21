#include "Piece.h"



Piece::Piece(std::string n, TypePiece t,Couleur c): nom(n), type(t), couleur(c) {}

std::set<Placement> Piece::getPlacements(const Plateau& p, bool premierTour) const
{
    std::set<Placement> places;
    std::map<Position, Case> cases = p.getCases();

    for (auto it = cases.begin(); it != cases.end(); ++it) {
        Position dest = (*it).first;
        if (p.peutPoser(dest, couleur, premierTour)) {
            places.insert(Placement(this, dest));
        }
    }

    return places;
}

std::ostream& operator<<(std::ostream& os, const Piece& p)
{
    os << p.nom << " (" << p.couleur << ")";
    return os;
}
