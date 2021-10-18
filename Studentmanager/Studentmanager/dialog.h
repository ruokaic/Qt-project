#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
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
    void ClearUserInterface();
    void WriteFile(QString);

private slots:
    void on_BT_yes_clicked();

    void on_BT_no_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
