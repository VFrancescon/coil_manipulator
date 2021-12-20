#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFileDialog *FileDialog = new QFileDialog;
    FileDialog->setOption(QFileDialog::DontUseNativeDialog, true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Field_Current_Toggle_stateChanged(int arg1)
{
    if(!arg1){
        //qDebug() << "Box is off\n";
        ui->A1_Top_Label->setText("Field");
        FieldToggle = true;
    }
    else{
        //qDebug() << "Box is on\n";
        ui->A1_Top_Label->setText("Current");
        FieldToggle = false;
    }

}

void MainWindow::on_X1_Slider_sliderReleased()
{
    //qDebug() << "Slider moved to: " << ui->X1_Slider->value() << "\n";
    ui->X1_SpinBox->setValue(ui->X1_Slider->value());
    x1_pos = ui->X1_Slider->value();
    if(FieldToggle){
        //do field stuff, X1
    }
    else{
        //do current stuff, X1
    }
}

void MainWindow::on_X1_SpinBox_editingFinished()
{
    //qDebug() << "Spinbox value: " << ui->X1_SpinBox->value() << "\n";
    ui->X1_Slider->setValue(ui->X1_SpinBox->value());
    x1_pos = ui->X1_SpinBox->value();
    if(FieldToggle){
        //do field stuff, X1
    }
    else{
        //do current stuff, X1
    }
}

void MainWindow::on_Y1_Slider_sliderReleased()
{
    //qDebug() << "Slider moved to: " << ui->Y1_Slider->value() << "\n";
    ui->Y1_SpinBox->setValue(ui->Y1_Slider->value());
    y1_pos = ui->Y1_Slider->value();
    if(FieldToggle){
        //do field stuff, X1
    }
    else{
        //do current stuff, X1
    }
}

void MainWindow::on_Y1_SpinBox_editingFinished()
{
    //qDebug() << "Spinbox value: " << ui->Y1_SpinBox->value() << "\n";
    ui->Y1_Slider->setValue(ui->Y1_SpinBox->value());
    y1_pos = ui->Y1_SpinBox->value();
    if(FieldToggle){
        //do field stuff, X1
    }
    else{
        //do current stuff, X1
    }
}

void MainWindow::on_Z1_Slider_sliderReleased()
{
    //qDebug() << "Slider moved to: " << ui->Z1_Slider->value() << "\n";
    ui->Z1_SpinBox->setValue(ui->Z1_Slider->value());
    y1_pos = ui->Z1_Slider->value();
    if(FieldToggle){
        //do field stuff, X1
    }
    else{
        //do current stuff, X1
    }
}

void MainWindow::on_Z1_SpinBox_editingFinished()
{
    //qDebug() << "Spinbox value: " << ui->Z1_SpinBox->value() << "\n";
    ui->Z1_Slider->setValue(ui->Z1_SpinBox->value());
    y1_pos = ui->Z1_SpinBox->value();
    if(FieldToggle){
        //do field stuff, X1
    }
    else{
        //do current stuff, X1
    }
}



void MainWindow::on_csvInput1_released()
{

    /* PROPER version to ship.
     *
     * FileName = FileDialog->getOpenFileName(this, "CSV File Path", "/home",
                                            tr("Csv files (*.csv)"));
    */
    //hacky fixed path so I don't have to click has many times every test
    FileName = FileDialog->getOpenFileName(this, "CSV File Path", "/home/vittorio/coil_manipulator",
                                                tr("Csv files (*.csv)"));


    /*To whoever is reading this, running this file dialog will print a
       "GtkDialog mapped without a transient parent. This is discouraged."
    According to the Qt forums, this is a bug. it's nothing major so I will ignore it for now.
    */

    qDebug() << "File name (or path?) is: " << FileName << "\n";

    csv_input_stream = std::fopen(FileName.toStdString(), "w");



}
