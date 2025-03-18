#pragma once

#include "Position.h"
#include "Plateau.h"

class Mouvement {
protected:
	Position dest;
public:
	Mouvement(Position dest): dest(dest) {}
	const Position& getDest() const { return dest; }
	virtual void executer(Plateau& p) const = 0;
	virtual void annuler(Plateau& p) const = 0;
	bool operator<(const Mouvement& other) const { return dest < other.dest; } // Ne sert qu'aux hachages pour les set, pas de logique particulière
};

class Deplacement: public Mouvement {
private:
    Position origine;
public:
	Deplacement(Position origine, Position dest): origine(origine), Mouvement(dest) {}
    const Position& getOrigine() const { return origine; }
	void executer(Plateau &p) const override;
	void annuler(Plateau& p) const override;		// Pas vraiment utile puisque nous utilisons le design pattern Memento, mais à laisser pour le polymorphisme
	friend std::ostream& operator<<(std::ostream& os, const Deplacement& deplacement);
};


class Placement: public Mouvement {
private:
    const Piece* piece;
public:
	Placement(const Piece* p, Position dest): piece(p), Mouvement(dest) {}
    const Piece* getPiece() const { return piece; }
	void executer(Plateau &p) const override;
	void annuler(Plateau& p) const override;
	friend std::ostream& operator<<(std::ostream& os, const Placement& placement);
};
