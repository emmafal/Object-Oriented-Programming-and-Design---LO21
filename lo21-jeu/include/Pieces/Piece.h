#pragma once

#include <set>
#include <string>
#include <iostream>

#include "Mouvement.h"
#include "Plateau.h"

#include "TypeInsecte.h"
#include "Couleur.h"
#include "Position.h"


class Piece {
private:
    std::string nom;
    TypePiece type;
    Couleur couleur;
public:
    Piece(std::string n, TypePiece i, Couleur c);
    Piece(const Piece& p) = delete;
    Piece& operator=(const Piece& p) = delete;
    virtual ~Piece() = default;
    
    const std::string& getNom() const { return nom; }
    TypePiece getType() const { return type; }
    Couleur getCouleur() const { return couleur; }
    
    virtual std::set<Deplacement> getDeplacements(Position origine, const Plateau& p) const = 0;
    virtual std::set<Placement> getPlacements(const Plateau& p, bool premierTour = false) const;

    friend std::ostream& operator<<(std::ostream& os, const Piece& p);
};
