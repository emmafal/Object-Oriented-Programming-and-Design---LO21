#pragma once
#include <vector>
#include "Position.h"
#include "Direction.h"



class Piece;

class Case {
private:
    Position pos;
    std::vector<const Piece *> pieces;
public:
    Case(Position p): pos(p) {}

    const Position& getPos() const { return pos; }

    size_t getNbPieces() const { return pieces.size(); }
    const Piece* getDernierePiece() const;
    bool estOccupee() const { return !pieces.empty(); }

    std::vector<Position> getVoisins() const;

    void poserPiece(const Piece* piece);
    void retirerPiece();

	class piece_iterator {
	private:
		std::vector<const Piece*>::const_iterator current;
		piece_iterator(std::vector<const Piece*>::const_iterator it): current(it) {}
	public:
		const Piece* operator*() const { return *current; }
		piece_iterator& operator++() { current++; return *this; };
		bool operator==(const piece_iterator& other) const { return current == other.current; }
		friend class Case;
	};

	class reverse_piece_iterator {
	private:
		std::vector<const Piece*>::const_iterator current;
		reverse_piece_iterator(std::vector<const Piece*>::const_iterator it) : current(it) {}
	public:
		const Piece* operator*() const { return *(current-1); }
		reverse_piece_iterator& operator++() { --current; return *this; };
		bool operator==(const reverse_piece_iterator& other) const { return current == other.current; }
		friend class Case;
	};

	piece_iterator begin() const { return piece_iterator(pieces.begin()); }
	piece_iterator end() const { return piece_iterator(pieces.end()); }

	reverse_piece_iterator rbegin() const { return reverse_piece_iterator(pieces.end()); }
	reverse_piece_iterator rend() const { return reverse_piece_iterator(pieces.begin()); }

};