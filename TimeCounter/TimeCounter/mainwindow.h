#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>
#include<QTime>
#include<QString>
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
    void timeflash();
    void on_BT_start_clicked();

    void on_BT_stop_clicked();

    void on_BT_pause_clicked();

    void on_BT_log_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTime basetime;
    QTime checktime;
    QString showtime;
};

#endif // MAINWINDOW_H
