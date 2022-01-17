#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt Headers
#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QDialog>
#include <QGraphicsView>
#include <QPainter>
#include <QPointF>
#include <QGraphicsItem>
#include <QPolygonF>
#include <QLineF>
#include <QGraphicsLineItem>

// Custom Qt Headers
#include "fancyslider.h"
#include "clickablerect.h"
#include "clickableview.h"
#include "arcitem.h"
#include "interactive_scene.h"

// C/C++ Headers
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#define CHECKBOX_ON 2
#define CHECKBOX_OFF 0


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /*File/Manual Control variables below */
    bool FieldToggle = true;
    int x1_pos=0;
    int y1_pos=0;
    int z1_pos=0;

    std::vector<int> csv_col1;
    std::vector<int> csv_col2;
    std::vector<int> csv_col3;

    int step_value = 0;
    /*File/Manual Control variables above */

    /*Drag/Drop Control members below */
//    QGraphicsScene *scene;
    interactive_scene *scene;
//    QGraphicsRectItem *rect;
//    QGraphicsRectItem *rect1;
//    ClickableRect *rect2;

    ClickableRect *green_rect;
    ClickableRect *blue_rect;
    ClickableRect *red_rect;
    QLineF *line;

    ArcItem *arc_l;

    QPointF green_rect_pos, blue_rect_pos, red_rect_pos;
    QGraphicsLineItem *line_item;
    QPainter *painter;

private slots:

    void on_Field_Current_Toggle_stateChanged(int arg1);

    /* Positive Sliders block */
    void on_X1_Slider_sliderReleased();
    void on_X1_SpinBox_editingFinished();
    void on_Y1_Slider_sliderReleased();
    void on_Y1_SpinBox_editingFinished();
    void on_Z1_Slider_sliderReleased();
    void on_Z1_SpinBox_editingFinished();

    /* Negative Sliders block */
//    void on_X2_Slider_sliderReleased();
//    void on_X2_SpinBox_editingFinished();
//    void on_Y2_Slider_sliderReleased();
//    void on_Y2_SpinBox_editingFinished();
//    void on_Z2_Slider_sliderReleased();
//    void on_Z2_SpinBox_editingFinished();

    void on_csvInputX1_released();

    void on_stepButton_released();

    /* Rectangle Coordinate Change slots */
    void on_xChanged();
    void on_yChanged();

private:
    Ui::MainWindow *ui;
    QString FileName;
    QFileDialog *FileDialog;
    std::ifstream csv_input;

};

#endif // MAINWINDOW_H
