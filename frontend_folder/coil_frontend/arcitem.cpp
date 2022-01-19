#include "arcitem.h"

ArcItem::ArcItem( qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent) :
    QGraphicsEllipseItem(x, y, width, height, parent) {
    rect = new QRectF(x, y, width, height);
}

void ArcItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget){
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawArc(*rect, startAngle(), spanAngle());
}

/*
    18/01/22
    Time to talk about generalising the arc lines

    Given two points P1 and P2, with coordinates (P1x, P1x), (P2x, P2y)

    4 cases are possible
    A: start =0, end =90
    P1x > P2x
    P1y > P2y

    B: start =90, end =180
    P1x < P2x
    P1y > P2y

    C: start =180, end =270
    P1x < P2x
    P1y < P2y

    D: start =270, end =360
    P1x > P2x
    P1y < P2y

    EXTRA CASE
    E: start =360, end =540
    P1x = P2x
    P1y > P2y

    F: start =180, end =360
    P1x = P2x
    P1y < P2y
*/
