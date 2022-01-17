#include "interactive_scene.h"

interactive_scene::interactive_scene(){

}


interactive_scene::interactive_scene(QObject *parent) : QGraphicsScene(parent){
}

interactive_scene::interactive_scene(const QRectF &sceneRect, QObject *parent) : QGraphicsScene(sceneRect, parent){

}

void interactive_scene::setup_rectangles(){
    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QBrush redBrush(Qt::red);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);

    Rect_W = RECT_W;
    Rect_H = RECT_H;
    Rect_W_2 = Rect_W /2;
    Rect_H_2 = Rect_H /2;

    QRectF generic_rect(0,0,Rect_W, Rect_H);

    red_rect = new ClickableRect(generic_rect);
    red_rect->setPos(100,0);
    this->addItem(red_rect);
    red_rect->setBrush(redBrush);
    red_rect->setPen(outlinePen);

    blue_rect = new ClickableRect(generic_rect);
    blue_rect->setPos(100,100);
    this->addItem(blue_rect);
    blue_rect->setBrush(blueBrush);
    blue_rect->setPen(outlinePen);

    green_rect = new ClickableRect(generic_rect);
    green_rect->setPos(100,200);
    this->addItem(green_rect);
    green_rect->setBrush(greenBrush);
    green_rect->setPen(outlinePen);

    this->UpdateRectPos();

}

void interactive_scene::setup_arcitem(){
    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QBrush redBrush(Qt::red);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);

    int start_angle = 90*16;
    int end_angle = 180*16;
    int span = (end_angle-start_angle);

    int h = abs((blue_rect_pos.y() - red_rect_pos.y()) * 2);
    int w = abs((blue_rect_pos.x() - red_rect_pos.x()) * 2);

    arc_top = new ArcItem(blue_rect_pos.x(), blue_rect_pos.y() - h/2 , w, h);
    arc_top->setSpanAngle(span);
    arc_top->setStartAngle(start_angle);
    this->addItem(arc_top);
    arc_top->setBrush(Qt::black);
    arc_top->setPen(outlinePen);
}

void interactive_scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    this->mouse_press_pos = event->scenePos();
    qDebug() << "NEW ITERATION------------------------------------------------";
    qDebug() << "click x pos: " << mouse_press_pos.x() << " y pos: " << mouse_press_pos.y();

    RR_X_BOOL = 0;
    RR_Y_BOOL = 0;
    BR_X_BOOL = 0;
    BR_Y_BOOL = 0;
    GR_X_BOOL = 0;
    GR_Y_BOOL = 0;
    RED_RECT_BOOL = 0;
    BLUE_RECT_BOOL = 0;
    GREEN_RECT_BOOL = 0;

    if(mouse_press_pos.x() <= (red_rect_pos.x() + Rect_W_2) && mouse_press_pos.x() >= (red_rect_pos.x() - Rect_W_2)) RR_X_BOOL = 1;
    if((mouse_press_pos.x() <= (green_rect_pos.x() + Rect_W_2)) && (mouse_press_pos.x() >= (green_rect_pos.x() - Rect_W_2))) GR_X_BOOL = 1;
    if(mouse_press_pos.x() <= (blue_rect_pos.x() + Rect_W_2) && mouse_press_pos.x() >= (blue_rect_pos.x() - Rect_W_2)) BR_X_BOOL = 1;

    if(mouse_press_pos.y() <= (red_rect_pos.y() + Rect_H_2) && mouse_press_pos.y() >= (red_rect_pos.y() - Rect_H_2)) RR_Y_BOOL = 1;
    if(mouse_press_pos.y() <= (blue_rect_pos.y() + Rect_H_2) && mouse_press_pos.y() >= (blue_rect_pos.y() - Rect_H_2)) BR_Y_BOOL = 1;
    if(mouse_press_pos.y() <= (green_rect_pos.y() + Rect_H_2) && mouse_press_pos.y() >= (green_rect_pos.y() - Rect_H_2)) GR_Y_BOOL = 1;

    if(RR_X_BOOL == 1 && RR_Y_BOOL == 1) RED_RECT_BOOL = 1;
    else if(BR_X_BOOL == 1 &&  BR_Y_BOOL == 1) BLUE_RECT_BOOL = 1;
    else if(GR_X_BOOL == 1 && GR_Y_BOOL == 1) GREEN_RECT_BOOL = 1;

}

void interactive_scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    this->mouse_release_pos = event->scenePos();
    qDebug() << "X pos released: " << mouse_release_pos.x() << " Y pos released: " << mouse_release_pos.y();
    if(RED_RECT_BOOL){
        this->red_rect->setPos(this->mouse_release_pos.x()-Rect_W_2, this->mouse_release_pos.y()-Rect_H_2);
        RED_RECT_BOOL = 0;
    }
    if(BLUE_RECT_BOOL){
        this->blue_rect->setPos(this->mouse_release_pos.x()-Rect_W_2, this->mouse_release_pos.y()-Rect_H_2);
        BLUE_RECT_BOOL = 0;
    }
    if(GREEN_RECT_BOOL){
        this->green_rect->setPos(this->mouse_release_pos.x()-Rect_W_2, this->mouse_release_pos.y()-Rect_H_2);
        GREEN_RECT_BOOL = 0;
    }

    this->UpdateRectPos();
    this->UpdateArc();
}

void interactive_scene::UpdateRectPos()
{
    green_rect_pos = this->green_rect->scenePos();
    blue_rect_pos = this->blue_rect->scenePos();
    red_rect_pos = this->red_rect->scenePos();

    QPointF p(Rect_W_2,Rect_W_2);

    green_rect_pos += p;
    red_rect_pos += p;
    blue_rect_pos += p;
}

void interactive_scene::UpdateArc()
{
    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QBrush redBrush(Qt::red);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);

    int start_angle = 90*16;
    int end_angle = 180*16;
    int span = (end_angle-start_angle);

    int h = abs((blue_rect_pos.y() - red_rect_pos.y()) * 2);
    int w = abs((blue_rect_pos.x() - red_rect_pos.x()) * 2);

    delete arc_top;
    arc_top = new ArcItem(blue_rect_pos.x(), blue_rect_pos.y() - h/2 , w, h);
    arc_top->setSpanAngle(span);
    arc_top->setStartAngle(start_angle);
    this->addItem(arc_top);
    arc_top->setBrush(Qt::black);
    arc_top->setPen(outlinePen);
}
