#ifndef INTERACTIVE_SCENE_H
#define INTERACTIVE_SCENE_H

#include <QGraphicsScene>
#include <QObject>
#include <QLineF>
#include <QPointF>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "clickablerect.h"
#include "arcitem.h"

#define RECT_W 20;
#define RECT_H 20;

class interactive_scene : public QGraphicsScene
{
    Q_OBJECT
public:
    interactive_scene();
    explicit interactive_scene(QObject *parent = nullptr);
    explicit interactive_scene(const QRectF &sceneRect, QObject *parent = nullptr);
    void setup_rectangles();
    void setup_arcitem();
signals:

public slots:


private:
    ClickableRect *green_rect;
    ClickableRect *blue_rect;
    ClickableRect *red_rect;
    QLineF *line;

    ArcItem *arc_top;
    ArcItem *arc_bottom;

    QPointF green_rect_pos, blue_rect_pos, red_rect_pos;
    QPainter *painter;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void UpdateRectPos();
    void UpdateArc();
    QPointF mouse_press_pos;
    QPointF mouse_release_pos;

    qreal Rect_H, Rect_W;
    qreal Rect_H_2, Rect_W_2;

    bool RR_X_BOOL = 0, RR_Y_BOOL = 0;
    bool BR_X_BOOL = 0, BR_Y_BOOL = 0;
    bool GR_X_BOOL = 0, GR_Y_BOOL = 0;
    bool RED_RECT_BOOL = 0;
    bool BLUE_RECT_BOOL = 0;
    bool GREEN_RECT_BOOL = 0;
};

#endif // INTERACTIVE_SCENE_H
