#ifndef HEXAGONITEM_H
#define HEXAGONITEM_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QPainter>
#include <QObject>
#include "PositionQt.h"

class HexagonItem : public QObject, public QGraphicsPolygonItem {
    Q_OBJECT

public:
    HexagonItem(qreal x, qreal y, qreal size, QGraphicsItem* parent = nullptr);

    void setImage(const QPixmap &pixmap);
    void setAxialCoordinates(PositionQt pos);
    void setAvailable(QColor couleur);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

signals:
    void hexagonClicked(HexagonItem* hexagon);

private:
    qreal hexSize;
    QPixmap image;
    PositionQt axialPos;
};

#endif // HEXAGONITEM_H
