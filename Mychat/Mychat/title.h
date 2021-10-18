#ifndef TITLE_H
#define TITLE_H

#include <QWidget>
#include <QMouseEvent>
#include <QMenu>
#include <QActionGroup>
#include <QAction>

namespace Ui {
class Title;
}

class Title : public QWidget
{
    Q_OBJECT

public:
    explicit Title(QWidget *parent = 0);
    ~Title();

private slots:
    void on_CloseBtn_clicked();
signals:
    void close();
private:
    Ui::Title *ui;
    QPoint x;

};

#endif // TITLE_H
