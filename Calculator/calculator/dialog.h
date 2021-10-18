#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include"cll.h"
#include<QString>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_BT_0_clicked();

    void on_BT_1_clicked();

    void on_BT_2_clicked();

    void on_BT_3_clicked();

    void on_BT_4_clicked();

    void on_BT_5_clicked();

    void on_BT_6_clicked();

    void on_BT_7_clicked();

    void on_BT_8_clicked();

    void on_BT_9_clicked();

    void on_BT_clear_clicked();

    void on_BT_add_clicked();

    void on_BT_sub_clicked();

    void on_BT_mul_clicked();

    void on_BT_div_clicked();

    void on_BT_eql_clicked();

private:
    Ui::Dialog *ui;
    QString num;
    Cll cll;
};

#endif // DIALOG_H
