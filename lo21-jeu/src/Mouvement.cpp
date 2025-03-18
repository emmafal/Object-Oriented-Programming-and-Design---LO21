#include "Mouvement.h"
#include "Plateau.h"
#include "Piece.h"

void Deplacement::executer(Plateau& p) const {
    p.deplacerPiece(origine, dest);
}

void Deplacement::annuler(Plateau& p) const
{
    p.deplacerPiece(dest, origine);
}

void Placement::executer(Plateau& p) const {
    p.placerPiece(piece, dest);
}


void Placement::annuler(Plateau& p) const
{
    p.supprimerPiece(dest);
}


std::ostream& operator<<(std::ostream& os, const Deplacement& deplacement)
{
    os << deplacement.origine << " -> " << deplacement.dest;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Placement& placement)
{
    os << *(placement.piece) << " -> " << placement.dest;
    return os;
}
