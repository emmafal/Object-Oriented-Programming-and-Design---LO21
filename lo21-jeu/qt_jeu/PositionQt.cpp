#include "PositionQt.h"
#include <cmath>
#include <QtGlobal> // Pour qreal

PositionQt::PositionQt(int q, int r) : q(q), r(r) {}

const int PositionQt::getQ() const { return q; }
const int PositionQt::getR() const { return r; }
const int PositionQt::getS() const { return -q - r; }

bool PositionQt::operator<(PositionQt other) const {
    return (q < other.q) || (q == other.q && r < other.r);
}

bool PositionQt::operator==(PositionQt other) const {
    return q == other.q && r == other.r;
}

PositionQt PositionQt::operator+(Direction dir) const {
    return PositionQt(q + dir.getQ(), r + dir.getR());
}


PositionQt PositionQt::fromPixel(qreal x, qreal y, qreal hexSize) {

    qreal hexWidth = std::sqrt(3) * hexSize;
    qreal hexHeight = 1.5 * hexSize;


    qreal qf = (x * std::sqrt(3) / 3 - y / 3) / hexSize;
    qreal rf = (y * 2.0 / 3.0) / hexSize;


    int r = std::round(rf);
    int q = std::round(qf);


    //int xOffset = r / 2;


    //q += xOffset;

    return PositionQt(q, r);
}







std::ostream& operator<<(std::ostream& os, PositionQt p) {
    os << "(" << p.getQ() << ", " << p.getR() << ")";
    return os;
}
