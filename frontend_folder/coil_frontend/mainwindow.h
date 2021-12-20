#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt Headers
#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include "fancyslider.h"

// C/C++ Headers
#include <fstream>

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
    bool FieldToggle = true;
    int x1_pos=0;
    int y1_pos=0;
    int z1_pos=0;

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

    void on_csvInput1_released();

private:
    Ui::MainWindow *ui;
    QString FileName;
    QFileDialog *FileDialog;
    std::ifstream csv_input_stream;

};

#endif // MAINWINDOW_H
