#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_OpenFileDialog_clicked();

    void on_Convert_clicked();

    void on_SaveFileDialog_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *csvModel;
    QStandardItemModel *jsonModel;
    QStandardItemModel *xmlReadModel;
    QStandardItemModel *xmlModel;
};
#endif // MAINWINDOW_H
