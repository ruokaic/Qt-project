#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"myscene.h"
#include<QCloseEvent>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event);

    ~MainWindow();

private slots:
    void UpdateScore();


private:
    Ui::MainWindow *ui;
    MyScene *sc;
    int score;
};

#endif // MAINWINDOW_H
