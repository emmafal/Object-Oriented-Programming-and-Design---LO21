#pragma once
#include <vector>



class Direction {
private:
    int q;
    int r;
public:
    Direction(int q = 0, int r = 0) : q(q), r(r) {}

    const int getQ() const { return q; }
    const int getR() const { return r; }

    static const Direction NW;
    static const Direction W;
    static const Direction SW;
    static const Direction NE;
    static const Direction E;
    static const Direction SE;

    static const std::vector<Direction> getDirs();

};
