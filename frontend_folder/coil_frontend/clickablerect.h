#ifndef CLICKABLERECT_H
#define CLICKABLERECT_H
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QMouseEvent>
#include <QEvent>
#include <QRectF>

class ClickableRect : public QGraphicsRectItem
{
protected:
    void mousePressEvent(QMouseEvent *event);
public:
    //ClickableRect();
    explicit ClickableRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
};

#endif // CLICKABLERECT_H
