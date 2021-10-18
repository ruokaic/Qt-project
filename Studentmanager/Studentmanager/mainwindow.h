#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"dialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionaddstu_triggered();

    void on_actionquerystu_triggered();

private:
    Ui::MainWindow *ui;
    Dialog a;
};

#endif // MAINWINDOW_H
