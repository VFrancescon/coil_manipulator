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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "clickableview.h"
#include "fancyslider.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGroupBox *csvBox;
    QFormLayout *formLayout;
    QLabel *CF_Label_CSV;
    QPushButton *csvInputX1;
    QPushButton *csvInputX2;
    QPushButton *csvInputY1;
    QPushButton *csvInputY2;
    QPushButton *csvInputZ1;
    QPushButton *csvInputZ2;
    QPushButton *csvInputINTR;
    QPushButton *pushButton;
    QPushButton *stepButton;
    QSpinBox *stepBox;
    QCheckBox *Field_Current_Toggle;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *Z1_Label;
    FancySlider *Z2_Slider;
    QSpinBox *Z1_SpinBox;
    FancySlider *Y2_Slider;
    QSpinBox *Z2_SpinBox;
    FancySlider *X2_Slider;
    QLabel *Y1_Label;
    QLabel *Z2_Label;
    QLabel *Y2_Label;
    FancySlider *Z1_Slider;
    QLabel *X2_Label;
    QSpinBox *Y2_SpinBox;
    QLabel *X1_Label;
    QSpinBox *Y1_SpinBox;
    FancySlider *Y1_Slider;
    QSpinBox *X2_SpinBox;
    FancySlider *X1_Slider;
    QLabel *CF_Label_MAN;
    QSpinBox *X1_SpinBox;
    QSpacerItem *verticalSpacer;
    ClickableView *graphicsViewL1;
    QMenuBar *menuBar;
    QMenu *menuCoil_Manipulator;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1622, 893);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        csvBox = new QGroupBox(centralWidget);
        csvBox->setObjectName(QStringLiteral("csvBox"));
        csvBox->setEnabled(true);
        formLayout = new QFormLayout(csvBox);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        CF_Label_CSV = new QLabel(csvBox);
        CF_Label_CSV->setObjectName(QStringLiteral("CF_Label_CSV"));
        CF_Label_CSV->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, CF_Label_CSV);

        csvInputX1 = new QPushButton(csvBox);
        csvInputX1->setObjectName(QStringLiteral("csvInputX1"));

        formLayout->setWidget(1, QFormLayout::LabelRole, csvInputX1);

        csvInputX2 = new QPushButton(csvBox);
        csvInputX2->setObjectName(QStringLiteral("csvInputX2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, csvInputX2);

        csvInputY1 = new QPushButton(csvBox);
        csvInputY1->setObjectName(QStringLiteral("csvInputY1"));

        formLayout->setWidget(2, QFormLayout::LabelRole, csvInputY1);

        csvInputY2 = new QPushButton(csvBox);
        csvInputY2->setObjectName(QStringLiteral("csvInputY2"));

        formLayout->setWidget(2, QFormLayout::FieldRole, csvInputY2);

        csvInputZ1 = new QPushButton(csvBox);
        csvInputZ1->setObjectName(QStringLiteral("csvInputZ1"));

        formLayout->setWidget(3, QFormLayout::LabelRole, csvInputZ1);

        csvInputZ2 = new QPushButton(csvBox);
        csvInputZ2->setObjectName(QStringLiteral("csvInputZ2"));

        formLayout->setWidget(3, QFormLayout::FieldRole, csvInputZ2);

        csvInputINTR = new QPushButton(csvBox);
        csvInputINTR->setObjectName(QStringLiteral("csvInputINTR"));

        formLayout->setWidget(4, QFormLayout::LabelRole, csvInputINTR);

        pushButton = new QPushButton(csvBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout->setWidget(4, QFormLayout::FieldRole, pushButton);

        stepButton = new QPushButton(csvBox);
        stepButton->setObjectName(QStringLiteral("stepButton"));

        formLayout->setWidget(5, QFormLayout::LabelRole, stepButton);

        stepBox = new QSpinBox(csvBox);
        stepBox->setObjectName(QStringLiteral("stepBox"));

        formLayout->setWidget(5, QFormLayout::FieldRole, stepBox);

        Field_Current_Toggle = new QCheckBox(csvBox);
        Field_Current_Toggle->setObjectName(QStringLiteral("Field_Current_Toggle"));
        QFont font;
        font.setPointSize(11);
        Field_Current_Toggle->setFont(font);

        formLayout->setWidget(6, QFormLayout::LabelRole, Field_Current_Toggle);


        gridLayout_2->addWidget(csvBox, 1, 0, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Z1_Label = new QLabel(groupBox);
        Z1_Label->setObjectName(QStringLiteral("Z1_Label"));

        gridLayout->addWidget(Z1_Label, 4, 0, 1, 1);

        Z2_Slider = new FancySlider(groupBox);
        Z2_Slider->setObjectName(QStringLiteral("Z2_Slider"));
        Z2_Slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Z2_Slider, 7, 1, 1, 1);

        Z1_SpinBox = new QSpinBox(groupBox);
        Z1_SpinBox->setObjectName(QStringLiteral("Z1_SpinBox"));
        QFont font1;
        font1.setPointSize(9);
        Z1_SpinBox->setFont(font1);

        gridLayout->addWidget(Z1_SpinBox, 4, 2, 1, 1);

        Y2_Slider = new FancySlider(groupBox);
        Y2_Slider->setObjectName(QStringLiteral("Y2_Slider"));
        Y2_Slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Y2_Slider, 6, 1, 1, 1);

        Z2_SpinBox = new QSpinBox(groupBox);
        Z2_SpinBox->setObjectName(QStringLiteral("Z2_SpinBox"));
        Z2_SpinBox->setFont(font1);

        gridLayout->addWidget(Z2_SpinBox, 7, 2, 1, 1);

        X2_Slider = new FancySlider(groupBox);
        X2_Slider->setObjectName(QStringLiteral("X2_Slider"));
        X2_Slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(X2_Slider, 5, 1, 1, 1);

        Y1_Label = new QLabel(groupBox);
        Y1_Label->setObjectName(QStringLiteral("Y1_Label"));

        gridLayout->addWidget(Y1_Label, 3, 0, 1, 1);

        Z2_Label = new QLabel(groupBox);
        Z2_Label->setObjectName(QStringLiteral("Z2_Label"));

        gridLayout->addWidget(Z2_Label, 7, 0, 1, 1);

        Y2_Label = new QLabel(groupBox);
        Y2_Label->setObjectName(QStringLiteral("Y2_Label"));

        gridLayout->addWidget(Y2_Label, 6, 0, 1, 1);

        Z1_Slider = new FancySlider(groupBox);
        Z1_Slider->setObjectName(QStringLiteral("Z1_Slider"));
        Z1_Slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Z1_Slider, 4, 1, 1, 1);

        X2_Label = new QLabel(groupBox);
        X2_Label->setObjectName(QStringLiteral("X2_Label"));

        gridLayout->addWidget(X2_Label, 5, 0, 1, 1);

        Y2_SpinBox = new QSpinBox(groupBox);
        Y2_SpinBox->setObjectName(QStringLiteral("Y2_SpinBox"));
        Y2_SpinBox->setFont(font1);

        gridLayout->addWidget(Y2_SpinBox, 6, 2, 1, 1);

        X1_Label = new QLabel(groupBox);
        X1_Label->setObjectName(QStringLiteral("X1_Label"));

        gridLayout->addWidget(X1_Label, 1, 0, 1, 1);

        Y1_SpinBox = new QSpinBox(groupBox);
        Y1_SpinBox->setObjectName(QStringLiteral("Y1_SpinBox"));
        Y1_SpinBox->setFont(font1);

        gridLayout->addWidget(Y1_SpinBox, 3, 2, 1, 1);

        Y1_Slider = new FancySlider(groupBox);
        Y1_Slider->setObjectName(QStringLiteral("Y1_Slider"));
        Y1_Slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Y1_Slider, 3, 1, 1, 1);

        X2_SpinBox = new QSpinBox(groupBox);
        X2_SpinBox->setObjectName(QStringLiteral("X2_SpinBox"));
        X2_SpinBox->setFont(font1);

        gridLayout->addWidget(X2_SpinBox, 5, 2, 1, 1);

        X1_Slider = new FancySlider(groupBox);
        X1_Slider->setObjectName(QStringLiteral("X1_Slider"));
        X1_Slider->setPageStep(0);
        X1_Slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(X1_Slider, 1, 1, 1, 1);

        CF_Label_MAN = new QLabel(groupBox);
        CF_Label_MAN->setObjectName(QStringLiteral("CF_Label_MAN"));

        gridLayout->addWidget(CF_Label_MAN, 0, 1, 1, 1);

        X1_SpinBox = new QSpinBox(groupBox);
        X1_SpinBox->setObjectName(QStringLiteral("X1_SpinBox"));
        X1_SpinBox->setFont(font1);

        gridLayout->addWidget(X1_SpinBox, 1, 2, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(1216, 383, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 1, 1, 1);

        graphicsViewL1 = new ClickableView(centralWidget);
        graphicsViewL1->setObjectName(QStringLiteral("graphicsViewL1"));

        gridLayout_2->addWidget(graphicsViewL1, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1622, 31));
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
        csvBox->setTitle(QApplication::translate("MainWindow", "CSV Controls", Q_NULLPTR));
        CF_Label_CSV->setText(QApplication::translate("MainWindow", "Field", Q_NULLPTR));
        csvInputX1->setText(QApplication::translate("MainWindow", "X+ Input", Q_NULLPTR));
        csvInputX2->setText(QApplication::translate("MainWindow", "X- Input", Q_NULLPTR));
        csvInputY1->setText(QApplication::translate("MainWindow", "Y+ Input", Q_NULLPTR));
        csvInputY2->setText(QApplication::translate("MainWindow", "Y- Input", Q_NULLPTR));
        csvInputZ1->setText(QApplication::translate("MainWindow", "Z+ Input", Q_NULLPTR));
        csvInputZ2->setText(QApplication::translate("MainWindow", "Z- Input", Q_NULLPTR));
        csvInputINTR->setText(QApplication::translate("MainWindow", "Introducer", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Run", Q_NULLPTR));
        stepButton->setText(QApplication::translate("MainWindow", "Step Through", Q_NULLPTR));
        Field_Current_Toggle->setText(QApplication::translate("MainWindow", "Toggle Field/Current", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Manual Controls", Q_NULLPTR));
        Z1_Label->setText(QApplication::translate("MainWindow", "Z+", Q_NULLPTR));
        Y1_Label->setText(QApplication::translate("MainWindow", "Y+", Q_NULLPTR));
        Z2_Label->setText(QApplication::translate("MainWindow", "Z-", Q_NULLPTR));
        Y2_Label->setText(QApplication::translate("MainWindow", "Y-", Q_NULLPTR));
        X2_Label->setText(QApplication::translate("MainWindow", "X-", Q_NULLPTR));
        X1_Label->setText(QApplication::translate("MainWindow", "X+", Q_NULLPTR));
        CF_Label_MAN->setText(QApplication::translate("MainWindow", "Field", Q_NULLPTR));
        menuCoil_Manipulator->setTitle(QApplication::translate("MainWindow", "Coil Manipulator", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
