#pragma once

#include <ostream>
#include "Direction.h"

class Position {
private:
    int q;
    int r;
public:
    Position(int q = 0, int r = 0): q(q), r(r) {}
    const int getQ() const { return q; }
    const int getR() const { return r; }
    const int getS() const { return -q - r; };

    bool operator<(Position other) const;
    bool operator==(Position other) const;

    Position operator+(Direction dir) const;
};

std::ostream& operator<<(std::ostream& os, Position p);
