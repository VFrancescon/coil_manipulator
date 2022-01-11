#include "clickablerect.h"

//ClickableRect::ClickableRect(){}

ClickableRect::ClickableRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsRectItem(x, y, width, height, parent)
{}

void ClickableRect::mousePressEvent(QMouseEvent *event){
    qDebug() << "Rectangle has been pressed\n";
    //QGraphicsRectItem::mouseReleaseEvent(event);

}

void ClickableRect::dragMoveEvent(QGraphicsSceneDragDropEvent *event){
    qDebug() << "Rectangle is being dragged\n";
}

void ClickableRect::dropEvent(QGraphicsSceneDragDropEvent *event){
    qDebug() << "Rectangle is being dropped\n";
}
