#ifndef CLICKABLEVIEW_H
#define CLICKABLEVIEW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QDebug>

class ClickableView : public QGraphicsView
{
protected:
    //void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *) override;
    void keyPressEvent(QKeyEvent * e) override;
    void scrollContentsBy(int,int) override;

    void resizeEvent(QResizeEvent *) override;
    void showEvent(QShowEvent *) override;

public:
    //ClickableView();
    explicit ClickableView(QWidget *parent = nullptr);
    void fitView();
};

#endif // CLICKABLEVIEW_H
