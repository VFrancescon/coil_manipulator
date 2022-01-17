#ifndef CLICKABLERECT_H
#define CLICKABLERECT_H
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QGraphicsSceneEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QRectF>

class ClickableRect : public QGraphicsRectItem
{
protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    QPointF UpdateCoordinates(QPointF pos);
    QPointF curr_pos;

    /*
    Big Revelation: Drag and Drop events are for dragging and dropping THINGS
    INTO the widget. Moving an item around needs to used MousePress and MouseRelease Events.
    Only lost two weeks to it, yay.
    */
//    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
//    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
public:
    //ClickableRect();
    explicit ClickableRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    explicit ClickableRect(const QRectF &rect, QGraphicsItem *parent = nullptr);
};

#endif // CLICKABLERECT_H
