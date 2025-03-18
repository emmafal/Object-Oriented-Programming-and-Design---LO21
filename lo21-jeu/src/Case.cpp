#include "Case.h"

std::vector<Position> Case::getVoisins() const
{
    std::vector<Position> voisins = {};
    std::vector<Direction> dirs = Direction::getDirs();
    for (auto it = dirs.begin(); it != dirs.end(); ++it) voisins.push_back(pos + *it);
    return voisins;
}

void Case::poserPiece(const Piece* piece)
{
    pieces.push_back(piece);
}

void Case::retirerPiece()
{
    if (estOccupee()) pieces.pop_back();
}

const Piece* Case::getDernierePiece() const {
    if (pieces.empty()) return nullptr;
    return pieces.back();
}

