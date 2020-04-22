/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *OpenFileDialog;
    QLineEdit *fileName;
    QPushButton *Convert;
    QTableView *tableView;
    QTableView *tableViewConv;
    QPushButton *SaveFileDialog;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(800, 603);
        MainWindow->setAutoFillBackground(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        OpenFileDialog = new QPushButton(centralwidget);
        OpenFileDialog->setObjectName(QString::fromUtf8("OpenFileDialog"));
        OpenFileDialog->setGeometry(QRect(9, 10, 81, 21));
        fileName = new QLineEdit(centralwidget);
        fileName->setObjectName(QString::fromUtf8("fileName"));
        fileName->setGeometry(QRect(100, 10, 591, 22));
        Convert = new QPushButton(centralwidget);
        Convert->setObjectName(QString::fromUtf8("Convert"));
        Convert->setEnabled(false);
        Convert->setGeometry(QRect(700, 10, 91, 21));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 40, 381, 511));
        tableView->horizontalHeader()->setMinimumSectionSize(50);
        tableView->horizontalHeader()->setDefaultSectionSize(50);
        tableView->horizontalHeader()->setStretchLastSection(false);
        tableView->verticalHeader()->setMinimumSectionSize(15);
        tableView->verticalHeader()->setDefaultSectionSize(15);
        tableViewConv = new QTableView(centralwidget);
        tableViewConv->setObjectName(QString::fromUtf8("tableViewConv"));
        tableViewConv->setGeometry(QRect(400, 40, 391, 511));
        tableViewConv->setSortingEnabled(false);
        tableViewConv->horizontalHeader()->setMinimumSectionSize(50);
        tableViewConv->horizontalHeader()->setDefaultSectionSize(50);
        tableViewConv->horizontalHeader()->setStretchLastSection(false);
        tableViewConv->verticalHeader()->setMinimumSectionSize(15);
        tableViewConv->verticalHeader()->setDefaultSectionSize(15);
        SaveFileDialog = new QPushButton(centralwidget);
        SaveFileDialog->setObjectName(QString::fromUtf8("SaveFileDialog"));
        SaveFileDialog->setEnabled(false);
        SaveFileDialog->setGeometry(QRect(710, 560, 81, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 19));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\275\320\262\320\265\321\200\321\202\320\265\321\200 CSV ---> XML", nullptr));
        OpenFileDialog->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        Convert->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\275\320\262\320\265\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        SaveFileDialog->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
