#include "HexagoneItem.h"

HexagonItem::HexagonItem(qreal x, qreal y, qreal size, QGraphicsItem* parent)
    : QGraphicsPolygonItem(parent), hexSize(size) {
    
    QPolygonF hexagon;
    for (int i = 0; i < 6; ++i) {
        qreal angle = M_PI / 3 * i + M_PI / 2;  
        qreal px = x + size * std::cos(angle);
        qreal py = y + size * std::sin(angle);
        hexagon << QPointF(px, py);
    }
    setPolygon(hexagon);
    setBrush(Qt::lightGray);
    setPen(QPen(Qt::black, 1));
}

void HexagonItem::setImage(const QPixmap &pixmap) {
    image = pixmap;
    update();  
}

void HexagonItem::setAvailable(QColor couleur) {
    setBrush(couleur);
    update();
}


void HexagonItem::setAxialCoordinates(PositionQt pos) {
    axialPos = pos;
}

void HexagonItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit hexagonClicked(this);  
    event->accept();
}

void HexagonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPolygonItem::paint(painter, option, widget);

    if (!image.isNull()) {
        QRectF rect = boundingRect();
        qreal imageWidth = image.width();
        qreal imageHeight = image.height();
        qreal scale = std::min(rect.width(), rect.height()) / std::max(imageWidth, imageHeight);
        qreal newWidth = imageWidth * scale;
        qreal newHeight = imageHeight * scale;
        qreal dx = (rect.width() - newWidth) / 2;
        qreal dy = (rect.height() - newHeight) / 2;

        painter->drawPixmap(rect.topLeft() + QPointF(dx, dy), image.scaled(newWidth, newHeight, Qt::KeepAspectRatio));
    }
}
