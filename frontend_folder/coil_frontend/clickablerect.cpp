#include "clickablerect.h"

//ClickableRect::ClickableRect(){}

ClickableRect::ClickableRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : QGraphicsRectItem(x, y, width, height, parent)
{
    setFlag(GraphicsItemFlag::ItemSendsScenePositionChanges);
    setFlag(QGraphicsItem::ItemIsMovable);
}

ClickableRect::ClickableRect(const QRectF &rect, QGraphicsItem *parent) : QGraphicsRectItem(rect, parent){
    setFlag(GraphicsItemFlag::ItemSendsScenePositionChanges);
    setFlag(QGraphicsItem::ItemIsMovable);
}

//void ClickableRect::mousePressEvent(QGraphicsSceneMouseEvent *event){
////    qreal x = event->buttonDownPos(Qt::AllButtons).x();
////    qreal y = event->buttonDownPos(Qt::AllButtons).y();

////    qreal x = event->pos().x();
////    qreal y = event->pos().y();


////    qDebug() << "Rectangle has been pressed at x = " << x << " and y = " << y << "\n";
//    //QGraphicsView::mousePressEvent(event);
//    //QGraphicsItem::mousePressEvent(event);
//    //QGraphicsRectItem::mouseReleaseEvent(event);
//    qDebug() << "Mouse press";
//}

//void ClickableRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){


//    /*
//    Immediately below is an attempt at tracking from mouse pos. Object snaps back and forth though.
//    */
////    QPointF point = event->scenePos();
////    qreal x = point.x();
////    qreal y = point.y();
////    qDebug() << "Rectangle has been released at x = " << x << " and y = " << y << "\n";
////    this->setPos(point);


//    /*
//    Different approach: track object pos since it can be moved already
//    */
//    QPointF point = this->scenePos();
//    qreal x = point.x();
//    qreal y = point.y();
//    qDebug() << "Rectangle has been released at x = " << x << " and y = " << y << "\n";
//    setPos(point);


//}

//void ClickableRect::dragMoveEvent(QGraphicsSceneDragDropEvent *event){
//    qDebug() << "Rectangle is being dragged\n";
//    event->
//    event->setAccepted(event->mimeData()->hasFormat("text/plain"));

//    QGraphicsItem::dragEnterEvent(event);
//    QGraphicsItem::dragLeaveEvent(event);
//}

//void ClickableRect::dropEvent(QGraphicsSceneDragDropEvent *event){
//    qDebug() << "Rectangle is being dropped\n";
//    QGraphicsItem::dragLeaveEvent(event);

//}

