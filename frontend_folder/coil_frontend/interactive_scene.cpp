#include "interactive_scene.h"

interactive_scene::interactive_scene(){
}


interactive_scene::interactive_scene(QObject *parent) : QGraphicsScene(parent){
}

interactive_scene::interactive_scene(const QRectF &sceneRect, QObject *parent) : QGraphicsScene(sceneRect, parent){

}

void interactive_scene::setupRectangles(){
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

void interactive_scene::setupTopArc(){
    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QBrush redBrush(Qt::red);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);
    outlinePen.setColor(Qt::red);
//    QPen outlinePen1 = outlinePen;
//    outlinePen1.setColor(Qt::blue);

    this->calculate_arc_angles(1);
    int h = abs((blue_rect_pos.y() - red_rect_pos.y()) * 2);
    int w = abs((blue_rect_pos.x() - red_rect_pos.x()) * 2);

//    QRectF top_arc_rect(blue_rect_pos.x(), blue_rect_pos.y() - h/2 , w, h);
//    ClickableRect * top_click_rect = new ClickableRect(top_arc_rect);
//    top_click_rect->setPos(0,0);
//    this->addItem(top_click_rect);
//    //top_click_rect->setBrush(blueBrush);
//    top_click_rect->setPen(outlinePen1);
//    ArcItem *test_arc = new ArcItem(blue_rect_pos.x(), blue_rect_pos.y() - h/2 , w, h);
//    test_arc->setSpanAngle(180*16);
//    test_arc->setStartAngle(360*16);
//    this->addItem(test_arc);
//    test_arc->setPen(outlinePen);


    arc_top = new ArcItem(blue_rect_pos.x(), blue_rect_pos.y() - h/2 , w, h);
    arc_top->setSpanAngle(top_span_angle*16);
    arc_top->setStartAngle(top_start_angle*16);
    this->addItem(arc_top);
    arc_top->setPen(outlinePen);


}

void interactive_scene::setupBottomArc(){
    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QBrush redBrush(Qt::red);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);
    outlinePen.setColor(Qt::blue);

    this->calculate_arc_angles(2);
    int h = abs((blue_rect_pos.y() - green_rect_pos.y()) * 2);
    int w = abs((blue_rect_pos.x() - green_rect_pos.x()) * 2);

    arc_bottom = new ArcItem(blue_rect_pos.x(), blue_rect_pos.y() - h/2, w, h);
    arc_bottom->setSpanAngle(bottom_span_angle*16);
    arc_bottom->setStartAngle(bottom_start_angle*16);
    this->addItem(arc_bottom);
    arc_bottom->setPen(outlinePen);
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
        int y_set = this->mouse_release_pos.y()-Rect_H_2;
        if( abs(this->mouse_release_pos.y()-this->red_rect_pos.y()) > 10 ) y_set = 10;

        this->red_rect->setPos(this->mouse_release_pos.x()-Rect_W_2, y_set);
    }
    if(BLUE_RECT_BOOL){
        this->blue_rect->setPos(this->mouse_release_pos.x()-Rect_W_2, this->mouse_release_pos.y()-Rect_H_2);

    }
    if(GREEN_RECT_BOOL){
        this->green_rect->setPos(this->mouse_release_pos.x()-Rect_W_2, this->mouse_release_pos.y()-Rect_H_2);

    }

    if(RED_RECT_BOOL || BLUE_RECT_BOOL || GREEN_RECT_BOOL)
    {
        this->UpdateRectPos();
        this->UpdateTopArc();
        this->UpdateBottomArc();
        RED_RECT_BOOL = 0;
        BLUE_RECT_BOOL = 0;
        GREEN_RECT_BOOL = 0;
    }
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

void interactive_scene::UpdateTopArc()
{
    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QBrush redBrush(Qt::red);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);
    outlinePen.setColor(Qt::red);

    calculate_arc_angles(1);
    int h = abs((blue_rect_pos.y() - red_rect_pos.y()) * 2);
    int w = abs((blue_rect_pos.x() - red_rect_pos.x()) * 2);

    delete arc_top;
    if(left_side) arc_top = new ArcItem(blue_rect_pos.x()-w, blue_rect_pos.y() - h/2 , w, h);
    else arc_top = new ArcItem(blue_rect_pos.x(), blue_rect_pos.y() - h/2 , w, h);

    arc_top->setSpanAngle(top_span_angle*16);
    arc_top->setStartAngle(top_start_angle*16);
    qDebug() << "top span " << top_span_angle << " top start " << top_start_angle;
    qDebug() << "top span " << arc_top->spanAngle() << " top start " << arc_top->startAngle();
    this->addItem(arc_top);
    arc_top->setBrush(Qt::black);
    arc_top->setPen(outlinePen);

}

void interactive_scene::UpdateBottomArc()
{
    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QBrush redBrush(Qt::red);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);
    outlinePen.setColor(Qt::blue);

    calculate_arc_angles(2);
    int h = abs((blue_rect_pos.y() - green_rect_pos.y()) * 2);
    int w = abs((blue_rect_pos.x() - green_rect_pos.x()) * 2);

    delete arc_bottom;
    if(left_side) arc_bottom = new ArcItem(blue_rect_pos.x()-w, blue_rect_pos.y() - h/2 , w, h);
    else arc_bottom = new ArcItem(blue_rect_pos.x(), blue_rect_pos.y() - h/2 , w, h);
    arc_bottom->setSpanAngle(bottom_span_angle*16);
    arc_bottom->setStartAngle(bottom_start_angle*16);
    this->addItem(arc_bottom);
    arc_bottom->setBrush(Qt::black);
    arc_bottom->setPen(outlinePen);
}

void interactive_scene::calculate_arc_angles(int opt)
{
    // set opt to 1 to set angles for top arc, 2 for bottom arc
    int arc_start_angle, arc_end_angle, arc_span;
    QPointF P1, P2;
    switch (opt) {
        case 1:
            P1 = blue_rect_pos;
            P2 = red_rect_pos;
            top_angle = true;
        break;
        case 2:
            P1 = blue_rect_pos;
            P2 = green_rect_pos;
            top_angle = false;
        break;
        default:
            return;
        break;
    }

    if(P1.x() > P2.x() && P1.y() > P2.y()) {
        qDebug() << "Case A";
        arc_start_angle = 0;
        arc_end_angle = 90;
        left_side = true;
    }
    if(P1.x() < P2.x() && P1.y() > P2.y()){
        qDebug() << "Case B";
        arc_start_angle = 90;
        arc_end_angle = 180;
        left_side = false;
    }
    if(P1.x() < P2.x() && P1.y() < P2.y()){
        qDebug() << "Case C";
        arc_start_angle = 180;
        arc_end_angle = 270;
        left_side = false;
    }
    if(P1.x() > P2.x() && P1.y() < P2.y()){
        qDebug() << "Case D";
        arc_start_angle = 270;
        arc_end_angle = 360;
        left_side = true;
    }
    if(P1.x() == P2.x() && P1.y() > P2.y()){
        arc_start_angle = 360;
        arc_end_angle = 540;
        left_side = false;

    }
    if(P1.x() == P2.x() && P1.y() < P2.y()){
        arc_start_angle = 180;
        arc_end_angle = 360;
        left_side = false;

    }

    arc_span = arc_end_angle - arc_start_angle;

    if(top_angle) {
        top_span_angle = arc_span;
        top_start_angle = arc_start_angle;
        top_end_angle = arc_end_angle;
    }
    else{
        bottom_span_angle = arc_span;
        bottom_start_angle = arc_start_angle;
        bottom_end_angle = arc_end_angle;
    }

    //qDebug() << "span " << arc_span << " start angle " << arc_start_angle << " end angle " << arc_end_angle;
}
