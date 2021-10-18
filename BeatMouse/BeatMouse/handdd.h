#ifndef HANDDD_H
#define HANDDD_H

#include <QObject>

class handdd : public QObject
{
    Q_OBJECT
private:
    explicit handdd(QObject *parent = nullptr);
    static handdd*hand;
public:
    static handdd* getInstance(){return hand;}
    void addScore();

signals:
    void beatMouse();
public slots:
};

#endif // HANDDD_H
