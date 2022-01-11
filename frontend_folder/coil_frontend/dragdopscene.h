#ifndef DRAGDROPSCENE_H
#define DRAGDROPSCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QDebug>

class DragDropScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit DragDropScene(QWidget *parent = nullptr);

protected:
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
};

#endif // DRAGDROPSCENE_H
