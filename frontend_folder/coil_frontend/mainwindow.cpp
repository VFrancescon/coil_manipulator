#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFileDialog *FileDialog = new QFileDialog;
    //setOption is meant to stop nutils from throwing errors, but does not work
    FileDialog->setOption(QFileDialog::DontUseNativeDialog, true);

    /*
    Graphics view setup
    scene is a pointer instance of qgraphics scene
    that we pair to a widget through ui->WidgetName->setscene
    */
    scene = new QGraphicsScene(this);
    ui->graphicsViewL1->setScene(scene);
    ui->graphicsViewL1->setDragMode(QGraphicsView::NoDrag);


    //brushes below
    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QBrush redBrush(Qt::red);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);

    //rect = scene->addRect(0,0, 50,50, outlinePen, greenBrush);
    rect = new QGraphicsRectItem(0,0,20,20);
    rect->setPos(100,100);
    scene->addItem(rect);

    rect1 = new QGraphicsRectItem(0,0,20,20);
    rect1->setPos(100,50);
    scene->addItem(rect1);

    rect2 = new ClickableRect(0,0,20,20);
    rect2->setPos(100,0);
    scene->addItem(rect2);

    rect->setBrush(greenBrush);
    rect->setPen(outlinePen);
    //rect->setFlag(QGraphicsItem::ItemIsMovable);

    rect1->setBrush(blueBrush);
    rect1->setPen(outlinePen);
    //rect1->setFlag(QGraphicsItem::ItemIsMovable);

    rect2->setBrush(redBrush);
    rect2->setPen(outlinePen);
    rect2->setFlag(QGraphicsItem::ItemIsMovable);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Field_Current_Toggle_stateChanged(int arg1)
{
    if(!arg1){
        //qDebug() << "Box is off\n";
        ui->CF_Label_CSV->setText("Field");
        ui->CF_Label_MAN->setText("Field");
        FieldToggle = true;
    }
    else{
        //qDebug() << "Box is on\n";
        ui->CF_Label_CSV->setText("Current");
        ui->CF_Label_MAN->setText("Current");
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



void MainWindow::on_csvInputX1_released()
{

    /* PROPER version to ship.

     * FileName = FileDialog->getOpenFileName(this, "CSV File Path", "/home",
                                            tr("Csv files (*.csv)"));
    */
    //hacky fixed path so I don't have to click as many times every test
    FileName = FileDialog->getOpenFileName(this, "CSV File Path", "/home/vittorio/coil_manipulator",
                                                tr("Csv files (*.csv)"));
    std::string filepath = FileName.toStdString();

    /*
    To whoever is reading this, running this file dialog will print a
       "GtkDialog mapped without a transient parent. This is discouraged." prompt
    According to the Qt forums, this is a bug. it's nothing major so I will ignore it for now.
    */

    //qDebug() << "File name (or path?) is: " << FileName << "\n";

    csv_input.open(filepath, std::ifstream::in);
    if(!csv_input.is_open()){
        qDebug() << "Failed to open file: " << FileName << "\n";
    }

    std::string line;
    std::getline(csv_input, line); //skip first line

    while ( std::getline(csv_input, line) ){

        if(line.empty()) break;
        std::stringstream iss(line);
        std::string lineStream;
        std::vector<int> row;
        while( std::getline(iss, lineStream, ',') ){
            row.push_back(std::stoi(lineStream));
        }
        csv_col1.push_back(row[0]);
        csv_col2.push_back(row[1]);
        csv_col3.push_back(row[2]);

    }

    qDebug() << "Printing results now\n";
    int vec_size = csv_col1.size();

    for(int i = 0; i < vec_size; i++){
        qDebug() << "Col1: " << csv_col1[i] << "Col2: " << csv_col2[i] << "Col3: " << csv_col3[i] << "\n";
    }


}

void MainWindow::on_stepButton_released()
{
    step_value = ui->stepBox->value();
    if(step_value == 0) {
        qDebug() << "Must enter a positive integer\n";
        return;
    }
    qDebug() << "Stepping through first " << step_value - 1 << "indeces of vectors\n";
}
