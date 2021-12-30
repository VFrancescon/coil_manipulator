#ifndef CLICKABLEVIEW_H
#define CLICKABLEVIEW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QDebug>

class ClickableView : public QGraphicsView
{
protected:
    void mousePressEvent(QMouseEvent *event);
public:
    //ClickableView();
    explicit ClickableView(QWidget *parent = nullptr);
};

#endif // CLICKABLEVIEW_H
