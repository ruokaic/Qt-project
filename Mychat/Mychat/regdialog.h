#ifndef REGDIALOG_H
#define REGDIALOG_H

#include <QDialog>
namespace Ui {
class regDialog;
}

class regDialog : public QDialog
{
    Q_OBJECT

public:
    explicit regDialog(QWidget *parent = nullptr);
    ~regDialog();
    void ClearUserInterface();
    bool ReadFile();
    void WriteFile(QString &str);
protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_btn_ok_clicked();

    void on_btn_no_clicked();

private:
    Ui::regDialog *ui;
     QStringList readfile;
};

#endif // REGDIALOG_H
