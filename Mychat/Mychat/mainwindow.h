#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma execution_character_set("utf-8")
#include <QWidget>

#include<QTcpServer>   //TCP服务端需要2种套接字：监听和通信套接字，记得先在pro文件添加network
#include<QTcpSocket>
#include<QFile>        //file可以是任意类型的文件。底层是byte
#include<QTimer>

namespace Ui {
class mainwindow;
}

struct header   //替换字符串做文件头部，但这样做发送文本也需要添加头部了
{
    int datatype;
    quint64 file_size ;
    QString file_name ;
    /*
     * 发送的时候：
     * tcpSocket->write((char *)&header_w, sizeof(header));
     * 接收的时候：
     * tcpSocket->read((char *)&header_r, sizeof(header));
     */
};
class mainwindow : public QWidget
{
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow();
    void send_data();
    void send(QTcpSocket *socket);
    void send_head(QTcpSocket *socket,QTimer &timer);

    void DealWithHead(QByteArray &buf);
    void DealWithData(QByteArray &buf);

    void ButtonInit();
    void Reset();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_btn_choose_clicked();

    void on_btn_send_clicked();

    void on_btn_connect_clicked();

    void on_btn_disconnect_clicked();


private:
    Ui::mainwindow *ui;
    quint16 port;

    QTcpServer *tcp_server = NULL;      //服务器端
    QTcpSocket *tcp_socket = NULL;
    QTimer timer;       //避免粘包
    QTimer heartbeat;    //判断客户端是否断开连接

    QTcpSocket *tcp_socket_2 = NULL;    //客户端
    QTimer timer_2;

    QFile file;         //发送方
    quint64 file_size ;
    QString file_name ;

    QFile file_2;       //接收方
    quint64 file_size_2;
    QString file_name_2;

    quint64 send_size;      //已发送文件的大小，通过与文件大小比较来判断文件是否发送完
    quint64 receive_size;

    bool isfile = false;    //用于接收时判断是文本还是文件
    bool isfile_2 = false;  //用于发送时判断文本还是文件
    bool isserver = true;   //判断是以服务器还是以客户端发送（服务器用socket通信,客户端用socket2）
    bool ishead = true;     //用于标记文件头的字节段落
};

#endif // MAINWINDOW_H
