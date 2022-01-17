#include "clickableview.h"

//ClickableView::ClickableView(){}

ClickableView::ClickableView(QWidget *parent) : QGraphicsView(parent){
    //QRectF rect = QRectF(-50,0, 400, 400);
    QRectF rect = this->sceneRect();
    QGraphicsView::setSceneRect(rect);
}

//void ClickableView::mousePressEvent(QMouseEvent *event){
//    QPointF pos;
//    pos = event->pos();
//    qDebug() << "Custom view clicked at x = " << pos.x() << " and y = " << pos.y();
//    QGraphicsView::mousePressEvent(event);
//}

void ClickableView::wheelEvent(QWheelEvent *){

}

void ClickableView::keyPressEvent(QKeyEvent * e) {
    QWidget::keyPressEvent(e);
}

//void ClickableView::scrollContentsBy(int , int){}

void ClickableView::resizeEvent(QResizeEvent *){
    this->fitView();
}

//void ClickableView::showEvent(QShowEvent *){
//    this->fitView();
//}

void ClickableView::fitView(){
    const QRectF rect = QRectF(0,0,250,250);
    this->fitInView(rect, Qt::KeepAspectRatio);
    this->setSceneRect(rect);
}
