#ifndef POSITIONQT_H
#define POSITIONQT_H

#include <ostream>
#include <QtGlobal>
#include "Direction.h"

class PositionQt {
private:
    int q;
    int r;

public:
    PositionQt(int q = 0, int r = 0);

    const int getQ() const;
    const int getR() const;
    const int getS() const;

    bool operator<(PositionQt other) const;
    bool operator==(PositionQt other) const;

    PositionQt operator+(Direction dir) const;


    static PositionQt fromPixel(qreal x, qreal y, qreal hexSize);
};


std::ostream& operator<<(std::ostream& os, PositionQt p);

#endif
