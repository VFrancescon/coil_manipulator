#include "clickablerect.h"

//ClickableRect::ClickableRect(){}

ClickableRect::ClickableRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsRectItem(x, y, width, height, parent)
{
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

QVariant ClickableRect::itemChange(GraphicsItemChange change, const QVariant &value){

    /* scene() returns 1 (or the scene) if the item is in a scene. sanity check*/
    //qDebug() << "The function is being called";
    if (change == ItemPositionChange && scene()) {
            // value is the new position.
            //qDebug() << "Item pos has changed";
            QPointF newPos = value.toPointF();
            QRectF rect = scene()->sceneRect();
            qDebug() << "1st IF New pos is: x = " << newPos.x() << " y = " << newPos.y() << "\n";
            if (!rect.contains(newPos)) {
                // Keep the item inside the scene rect.
                newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
                newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));

                //qDebug() << "2nd IF New pos is: x = " << newPos.x() << " y = " << newPos.y() << "\n";
                return newPos;
            }
        }
        return QGraphicsItem::itemChange(change, value);

}
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

