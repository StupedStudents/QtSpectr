/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLCDNumber *lcdNumber;
    QProgressBar *progressBar_7;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QProgressBar *progressBar_6;
    QProgressBar *progressBar_5;
    QProgressBar *progressBar_4;
    QProgressBar *progressBar_3;
    QProgressBar *progressBar_2;
    QProgressBar *progressBar;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *label_11;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_7;
    QLabel *label_10;
    QProgressBar *progressBar_8;
    QLabel *label_2;
    QLabel *label_3;
    QLCDNumber *lcdNumber_2;
    QComboBox *comboBox;
    QLabel *label_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setMaximumSize(QSize(800, 600));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(110, 150, 201, 111));
        progressBar_7 = new QProgressBar(centralWidget);
        progressBar_7->setObjectName(QStringLiteral("progressBar_7"));
        progressBar_7->setGeometry(QRect(73, 340, 311, 23));
        progressBar_7->setMaximum(350);
        progressBar_7->setValue(24);
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(490, 130, 281, 351));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        progressBar_6 = new QProgressBar(horizontalLayoutWidget);
        progressBar_6->setObjectName(QStringLiteral("progressBar_6"));
        progressBar_6->setValue(100);
        progressBar_6->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(progressBar_6);

        progressBar_5 = new QProgressBar(horizontalLayoutWidget);
        progressBar_5->setObjectName(QStringLiteral("progressBar_5"));
        progressBar_5->setValue(100);
        progressBar_5->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(progressBar_5);

        progressBar_4 = new QProgressBar(horizontalLayoutWidget);
        progressBar_4->setObjectName(QStringLiteral("progressBar_4"));
        progressBar_4->setValue(100);
        progressBar_4->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(progressBar_4);

        progressBar_3 = new QProgressBar(horizontalLayoutWidget);
        progressBar_3->setObjectName(QStringLiteral("progressBar_3"));
        progressBar_3->setValue(100);
        progressBar_3->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(progressBar_3);

        progressBar_2 = new QProgressBar(horizontalLayoutWidget);
        progressBar_2->setObjectName(QStringLiteral("progressBar_2"));
        progressBar_2->setValue(100);
        progressBar_2->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(progressBar_2);

        progressBar = new QProgressBar(horizontalLayoutWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(100);
        progressBar->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(progressBar);

        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(510, 90, 261, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        label->setAutoFillBackground(false);
        label->setScaledContents(false);

        horizontalLayout_2->addWidget(label);

        label_11 = new QLabel(horizontalLayoutWidget_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setFont(font);
        label_11->setAutoFillBackground(false);
        label_11->setScaledContents(false);

        horizontalLayout_2->addWidget(label_11);

        label_8 = new QLabel(horizontalLayoutWidget_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font);
        label_8->setAutoFillBackground(false);
        label_8->setScaledContents(false);

        horizontalLayout_2->addWidget(label_8);

        label_9 = new QLabel(horizontalLayoutWidget_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font);
        label_9->setAutoFillBackground(false);
        label_9->setScaledContents(false);

        horizontalLayout_2->addWidget(label_9);

        label_7 = new QLabel(horizontalLayoutWidget_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font);
        label_7->setAutoFillBackground(false);
        label_7->setScaledContents(false);

        horizontalLayout_2->addWidget(label_7);

        label_10 = new QLabel(horizontalLayoutWidget_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font);
        label_10->setAutoFillBackground(false);
        label_10->setScaledContents(false);

        horizontalLayout_2->addWidget(label_10);

        progressBar_8 = new QProgressBar(centralWidget);
        progressBar_8->setObjectName(QStringLiteral("progressBar_8"));
        progressBar_8->setGeometry(QRect(73, 300, 311, 23));
        progressBar_8->setMaximum(100);
        progressBar_8->setValue(24);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(8, 300, 61, 20));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(23, 344, 46, 13));
        lcdNumber_2 = new QLCDNumber(centralWidget);
        lcdNumber_2->setObjectName(QStringLiteral("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(70, 380, 64, 23));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(100, 420, 371, 22));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 420, 61, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMovable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        progressBar_6->setFormat(QString());
        progressBar_5->setFormat(QString());
        progressBar_4->setFormat(QString());
        progressBar_3->setFormat(QString());
        progressBar_2->setFormat(QString());
        progressBar->setFormat(QString());
        label->setText(QApplication::translate("MainWindow", "E", 0));
        label_11->setText(QApplication::translate("MainWindow", "A", 0));
        label_8->setText(QApplication::translate("MainWindow", "D", 0));
        label_9->setText(QApplication::translate("MainWindow", "G", 0));
        label_7->setText(QApplication::translate("MainWindow", "B", 0));
        label_10->setText(QApplication::translate("MainWindow", "E", 0));
        label_2->setText(QApplication::translate("MainWindow", "\320\220\320\274\320\277\320\273\320\270\321\202\321\203\320\264\320\260", 0));
        label_3->setText(QApplication::translate("MainWindow", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260", 0));
        label_4->setText(QApplication::translate("MainWindow", "\320\234\320\270\320\272\321\200\320\276\321\204\320\276\320\275", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
