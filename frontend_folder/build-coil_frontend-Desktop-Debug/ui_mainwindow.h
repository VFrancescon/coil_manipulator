/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "fancyslider.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *sliderBox;
    FancySlider *X2_Slider;
    FancySlider *Y1_Slider;
    FancySlider *Z1_Slider;
    FancySlider *X1_Slider;
    FancySlider *Y2_Slider;
    QLabel *A1_Top_Label;
    FancySlider *Z2_Slider;
    QLabel *Y2_Label;
    QLabel *Z2_Label;
    QLabel *X1_Label;
    QLabel *X2_Label;
    QLabel *Y1_Label;
    QLabel *Z1_Label;
    QCheckBox *Field_Current_Toggle;
    QSpinBox *X1_SpinBox;
    QSpinBox *Y1_SpinBox;
    QSpinBox *Z1_SpinBox;
    QSpinBox *Z2_SpinBox;
    QSpinBox *Y2_SpinBox;
    QSpinBox *X2_SpinBox;
    QPushButton *csvInput1;
    QMenuBar *menuBar;
    QMenu *menuCoil_Manipulator;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1245, 893);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sliderBox = new QGroupBox(centralWidget);
        sliderBox->setObjectName(QStringLiteral("sliderBox"));
        sliderBox->setGeometry(QRect(850, 20, 380, 500));
        X2_Slider = new FancySlider(sliderBox);
        X2_Slider->setObjectName(QStringLiteral("X2_Slider"));
        X2_Slider->setGeometry(QRect(50, 160, 260, 20));
        X2_Slider->setOrientation(Qt::Horizontal);
        Y1_Slider = new FancySlider(sliderBox);
        Y1_Slider->setObjectName(QStringLiteral("Y1_Slider"));
        Y1_Slider->setGeometry(QRect(50, 100, 260, 20));
        Y1_Slider->setOrientation(Qt::Horizontal);
        Z1_Slider = new FancySlider(sliderBox);
        Z1_Slider->setObjectName(QStringLiteral("Z1_Slider"));
        Z1_Slider->setGeometry(QRect(50, 130, 260, 20));
        Z1_Slider->setOrientation(Qt::Horizontal);
        X1_Slider = new FancySlider(sliderBox);
        X1_Slider->setObjectName(QStringLiteral("X1_Slider"));
        X1_Slider->setGeometry(QRect(50, 70, 260, 20));
        X1_Slider->setPageStep(0);
        X1_Slider->setOrientation(Qt::Horizontal);
        Y2_Slider = new FancySlider(sliderBox);
        Y2_Slider->setObjectName(QStringLiteral("Y2_Slider"));
        Y2_Slider->setGeometry(QRect(50, 190, 260, 20));
        Y2_Slider->setOrientation(Qt::Horizontal);
        A1_Top_Label = new QLabel(sliderBox);
        A1_Top_Label->setObjectName(QStringLiteral("A1_Top_Label"));
        A1_Top_Label->setGeometry(QRect(140, 45, 81, 23));
        A1_Top_Label->setAlignment(Qt::AlignCenter);
        Z2_Slider = new FancySlider(sliderBox);
        Z2_Slider->setObjectName(QStringLiteral("Z2_Slider"));
        Z2_Slider->setGeometry(QRect(50, 220, 260, 20));
        Z2_Slider->setOrientation(Qt::Horizontal);
        Y2_Label = new QLabel(sliderBox);
        Y2_Label->setObjectName(QStringLiteral("Y2_Label"));
        Y2_Label->setGeometry(QRect(20, 190, 30, 20));
        Z2_Label = new QLabel(sliderBox);
        Z2_Label->setObjectName(QStringLiteral("Z2_Label"));
        Z2_Label->setGeometry(QRect(20, 220, 30, 20));
        X1_Label = new QLabel(sliderBox);
        X1_Label->setObjectName(QStringLiteral("X1_Label"));
        X1_Label->setGeometry(QRect(20, 70, 30, 20));
        X2_Label = new QLabel(sliderBox);
        X2_Label->setObjectName(QStringLiteral("X2_Label"));
        X2_Label->setGeometry(QRect(20, 160, 30, 20));
        Y1_Label = new QLabel(sliderBox);
        Y1_Label->setObjectName(QStringLiteral("Y1_Label"));
        Y1_Label->setGeometry(QRect(20, 100, 30, 20));
        Z1_Label = new QLabel(sliderBox);
        Z1_Label->setObjectName(QStringLiteral("Z1_Label"));
        Z1_Label->setGeometry(QRect(20, 130, 30, 20));
        Field_Current_Toggle = new QCheckBox(sliderBox);
        Field_Current_Toggle->setObjectName(QStringLiteral("Field_Current_Toggle"));
        Field_Current_Toggle->setGeometry(QRect(20, 250, 260, 40));
        QFont font;
        font.setPointSize(11);
        Field_Current_Toggle->setFont(font);
        X1_SpinBox = new QSpinBox(sliderBox);
        X1_SpinBox->setObjectName(QStringLiteral("X1_SpinBox"));
        X1_SpinBox->setGeometry(QRect(320, 62, 50, 30));
        QFont font1;
        font1.setPointSize(9);
        X1_SpinBox->setFont(font1);
        Y1_SpinBox = new QSpinBox(sliderBox);
        Y1_SpinBox->setObjectName(QStringLiteral("Y1_SpinBox"));
        Y1_SpinBox->setGeometry(QRect(320, 93, 50, 30));
        Y1_SpinBox->setFont(font1);
        Z1_SpinBox = new QSpinBox(sliderBox);
        Z1_SpinBox->setObjectName(QStringLiteral("Z1_SpinBox"));
        Z1_SpinBox->setGeometry(QRect(320, 124, 50, 30));
        Z1_SpinBox->setFont(font1);
        Z2_SpinBox = new QSpinBox(sliderBox);
        Z2_SpinBox->setObjectName(QStringLiteral("Z2_SpinBox"));
        Z2_SpinBox->setGeometry(QRect(320, 217, 50, 30));
        Z2_SpinBox->setFont(font1);
        Y2_SpinBox = new QSpinBox(sliderBox);
        Y2_SpinBox->setObjectName(QStringLiteral("Y2_SpinBox"));
        Y2_SpinBox->setGeometry(QRect(320, 186, 50, 30));
        Y2_SpinBox->setFont(font1);
        X2_SpinBox = new QSpinBox(sliderBox);
        X2_SpinBox->setObjectName(QStringLiteral("X2_SpinBox"));
        X2_SpinBox->setGeometry(QRect(320, 155, 50, 30));
        X2_SpinBox->setFont(font1);
        csvInput1 = new QPushButton(centralWidget);
        csvInput1->setObjectName(QStringLiteral("csvInput1"));
        csvInput1->setGeometry(QRect(290, 430, 130, 37));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1245, 31));
        menuCoil_Manipulator = new QMenu(menuBar);
        menuCoil_Manipulator->setObjectName(QStringLiteral("menuCoil_Manipulator"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuCoil_Manipulator->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        sliderBox->setTitle(QApplication::translate("MainWindow", "Manual Controls", Q_NULLPTR));
        A1_Top_Label->setText(QApplication::translate("MainWindow", "Field", Q_NULLPTR));
        Y2_Label->setText(QApplication::translate("MainWindow", "Y-", Q_NULLPTR));
        Z2_Label->setText(QApplication::translate("MainWindow", "Z-", Q_NULLPTR));
        X1_Label->setText(QApplication::translate("MainWindow", "X+", Q_NULLPTR));
        X2_Label->setText(QApplication::translate("MainWindow", "X-", Q_NULLPTR));
        Y1_Label->setText(QApplication::translate("MainWindow", "Y+", Q_NULLPTR));
        Z1_Label->setText(QApplication::translate("MainWindow", "Z+", Q_NULLPTR));
        Field_Current_Toggle->setText(QApplication::translate("MainWindow", "Toggle Field/Current", Q_NULLPTR));
        csvInput1->setText(QApplication::translate("MainWindow", "OpenFile", Q_NULLPTR));
        menuCoil_Manipulator->setTitle(QApplication::translate("MainWindow", "Coil Manipulator", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
