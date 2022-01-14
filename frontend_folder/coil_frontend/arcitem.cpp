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
