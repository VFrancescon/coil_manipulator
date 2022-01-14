#ifndef ARCITEM_H
#define ARCITEM_H

#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QPainter>

class ArcItem : public QGraphicsEllipseItem
{
public:
    explicit ArcItem ( qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0 );
    ArcItem();
    QRectF *rect;
protected:
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
};

#endif // ARCITEM_H
