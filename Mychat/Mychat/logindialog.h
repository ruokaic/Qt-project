#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include"mainwindow.h"
#include"regdialog.h"
#include"title.h"
#include <QDialog>
#include<QStringList>

namespace Ui {
class logindialog;
}

class logindialog : public QDialog
{
    Q_OBJECT

public:
    explicit logindialog(QWidget *parent = nullptr);
    ~logindialog();
    bool ReadFile();
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void on_btn_login_clicked();

    void on_btn_register_clicked();

private:
    Ui::logindialog *ui;
    mainwindow *mainw;
    mainwindow *mainw2;
    QStringList readfile;

    bool WinDrag;
    QPoint x;
};

#endif // LOGINDIALOG_H
