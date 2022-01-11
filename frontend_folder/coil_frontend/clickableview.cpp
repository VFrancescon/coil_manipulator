#include "clickableview.h"

//ClickableView::ClickableView(){}

ClickableView::ClickableView(QWidget *parent) : QGraphicsView(parent){
    //QRectF rect = QRectF(-0.5,-0.5, 1, 1);
    QRectF rect = this->sceneRect();
    QGraphicsView::setSceneRect(rect);
}

//void ClickableView::mousePressEvent(QMouseEvent *event){
//    qDebug() << "Custom view clicked.";
//    QGraphicsView::mousePressEvent(event);
//}

void ClickableView::wheelEvent(QWheelEvent *){

}

void ClickableView::keyPressEvent(QKeyEvent * e) {
    QWidget::keyPressEvent(e);
}

void ClickableView::scrollContentsBy(int , int){

}

void ClickableView::resizeEvent(QResizeEvent *){
    this->fitView();
}

void ClickableView::showEvent(QShowEvent *){
    this->fitView();
}

void ClickableView::fitView(){
    const QRectF rect = QRectF(0,0,250,250);
    this->fitInView(rect, Qt::KeepAspectRatio);
    this->setSceneRect(rect);
}
