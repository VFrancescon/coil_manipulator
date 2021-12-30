#include "clickableview.h"

//ClickableView::ClickableView(){}

ClickableView::ClickableView(QWidget *parent) : QGraphicsView(parent){

}

void ClickableView::mousePressEvent(QMouseEvent *event){
    qDebug() << "Custom view clicked.";
    QGraphicsView::mousePressEvent(event);
}
