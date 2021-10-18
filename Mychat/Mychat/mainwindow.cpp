#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<ctime>
#include<cstdlib>
#include<QMessageBox>
#include<QPainter>
#include<QDebug>
#include<QFileDialog>   //文件窗口，用于选择要打开的文件路径
#include<QFileInfo>    //获取文件信息

mainwindow::mainwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);
    srand((unsigned int)time(0));
    port = rand()%65536;
    this->setWindowTitle( "端口号："+QString::number(port,10));

    ui->btn_choose->setEnabled(false);
    ui->btn_send->setEnabled(false);

    tcp_server = new QTcpServer(this);
    tcp_socket_2 = new QTcpSocket(this);

    tcp_server->listen(QHostAddress::Any,port);         //监听端口的连接请求

    connect(tcp_server,&QTcpServer::newConnection,      //监听到客户端发出的请求，成功连接后发出了信号，触发槽函数
           [=]()
           {
               tcp_socket = tcp_server->nextPendingConnection();        //获取通信套接字

               QString temp =  "以服务器端连接";

               ui->text_output->append(temp);           //打印连接成功消息 

               ButtonInit();        //连接成功，按钮可用

               connect(tcp_socket,&QTcpSocket::readyRead,               //接收信息
                       [=]()
                       {         
                           QByteArray buf = tcp_socket->readAll();
                           if(QString(buf).section('#',0,0)=="File")    //判断是文本还是文件
                               isfile = true;
                           if(!isfile)
                           {
                               QString str = "RECEIVE:" + buf;
                               ui->text_output->append(str);            //不是文件，则直接显示文本

                           }
                           else
                           {
                               if(ishead)               //接收文件头
                               { 
                                   ishead = false;               
                                   DealWithHead(buf); 
                               }
                               else                     //接收文件
                                   DealWithData(buf);
                           }
                       }
                       );
               connect(tcp_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
                       [=]()
                       {
                           int error = tcp_socket->error();
                           switch(error)
                           {
                               case QAbstractSocket::RemoteHostClosedError://客户端断开
                               {
                                   ui->text_output->append( "断开与客户端连接");
                                   Reset();
                                   break;
                               }
                           }
                       }
                       );
           }
           );



    connect(tcp_socket_2,&QTcpSocket::connected,
           [=]()
           {
               ui->text_output->append( "以客户端连接");
               ButtonInit();                            //连接成功，按钮可用
           }
           );

    connect(tcp_socket_2,&QTcpSocket::readyRead,         //接收信息
           [=]()
           {
               QByteArray buf = tcp_socket_2->readAll();
               if(QString(buf).section('#',0,0)=="File")        //判断是否是文件
                   isfile = true;
               if(!isfile)
               {
                   QString str = "RECEIVE:"+ buf;
                    ui->text_output->append(str);
               }
               else
               {
                   if(ishead)           //处理文件头
                   {
                       ishead = false;
                       DealWithHead(buf);
                   }
                   else                 //接收文件
                       DealWithData(buf);
               }
           }
           );

   connect(&timer,&QTimer::timeout,
           [=]()
            {
                timer.stop();
                send_data();
            }
            );
   connect(&timer_2,&QTimer::timeout,
           [=]()
            {
                timer_2.stop();
                send_data();
            }
            );

   connect(tcp_socket_2,&QTcpSocket::disconnected,  //客户端
           [=]()
            {
                ui->text_output->append( "断开与服务器连接");
                Reset();
            }
            );
}

mainwindow::~mainwindow()
{
    delete ui;
}

void mainwindow::on_btn_choose_clicked()        //选择文件，并获取文件信息
{
    QString path = QFileDialog::getOpenFileName(this,"open","../");
    if(path!=nullptr)
    {
        file.setFileName(path);

        //初始化文件信息
        file_size = 0;
        file_name.clear();
        send_size = 0;

        //使用QFileinfo获取文件信息（用于建立文件头）
        QFileInfo info(path);
        file_size = info.size();
        file_name = info.fileName();

        if(!file.open(QIODevice::ReadOnly))     //必须先打开文件再传输文件
            qDebug()<<"can not open";
        else {
            ui->text_output->append(path);      //提示被选文件路径

            isfile_2 = true;                    //传输内容是文件不是文本

            ui->btn_choose->setEnabled(false);  //选择完成
            }
    }
    else {
        qDebug()<<"路径无效";
    }

}

void mainwindow::on_btn_send_clicked()
{
    if(!isfile_2)   //发送文本
    {
        if(!isserver)
        {
            //以客户端发送
            QString str = ui->text_input->toPlainText();
            tcp_socket_2->write(str.toUtf8());
            ui->text_output->append(str);
            ui->text_input->clear();
        }
        else {
            //以服务器端发送
            QString str = ui->text_input->toPlainText();
            tcp_socket->write(str.toUtf8());
            ui->text_output->append(str);
            ui->text_input->clear();
        }
    }
    else     //发送文件
    {
        if(!isserver)
            send_head(tcp_socket_2,timer_2);    //以客户端发送
        else
            send_head(tcp_socket,timer);        //以服务器端发送
    }
}

void mainwindow::send_head(QTcpSocket *socket,QTimer &timer)    //发送文件头
{
    //发送文件头部信息（文件名及大小）
    QString temp = QString("File#%1#%2").arg(file_name).arg(file_size);     //用#分割，便于读取时拆分

    qint64 len = socket->write(temp.toUtf8());                              //发送

    if(len > 0)                                 //文件头发送成功
        timer.start(20);                        //20ms后发送文件本体
    else
    {
        qDebug() <<"文件头发送失败";
        ui->btn_choose->setEnabled(true);       //重新选择文件
        ui->btn_send->setEnabled(false);
    }
}

void mainwindow::send_data()
{    
    if(!isserver)
    {
        //以客户端发送
        send(tcp_socket_2);
    }
    else
    {
        //以服务器端发送
        send(tcp_socket);
    }
}

void mainwindow::send(QTcpSocket *socket)
{

    qint64 len = 0;
    do{
        char buf[4*1024] = {0};                 //每次读取4k数据
        len = 0;
        len = file.read(buf,sizeof(buf));       //读取文件数据，记录所读数据长度

        len = socket->write(buf,len);           //每次循环对方将触发readready信号

        send_size += len;                       //记录已发送数据长度

    }while(len > 0);

    if(send_size == file_size)                  //已发数据等于文件大小则发送完毕
    {
        ui->text_output->append( "文件发送完毕");
        file.close();
        file_name = "";
        ui->btn_choose->setEnabled(true);
        isfile_2 = false;
    }
}


void mainwindow::DealWithHead(QByteArray &buf)  //接收头部
{
    //文件头拆包
    file_name_2 = QString(buf).section('#',1,1);                //后两个参数是区间，这里表示被#分隔的第二个元素
    file_size_2 = QString(buf).section('#',2,2).toInt();
    receive_size = 0;
    file_2.setFileName(file_name_2);
    if(!file_2.open(QIODevice::WriteOnly))
        qDebug()<<file_name_2 <<"can not open";
}

void mainwindow::DealWithData(QByteArray &buf)  //接收文件本体
{
    qint64 len = file_2.write(buf);
    receive_size += len;

    if(receive_size == file_size_2)
    {
         ui->text_output->append( "文件接收完毕");
         file_2.close();
         isfile = false;
         file_name_2 = "";
    }

}

void mainwindow::on_btn_connect_clicked()       //以客户端身份请求连接
{
    QString str = ui->lineEdit_port->text();
    QString IP = ui->lineEdit_IP->text();
    if(str != NULL && IP != NULL)
    {
        quint16 port = str.toInt();
        tcp_socket_2->connectToHost(IP,port);
        isserver = false;                     //成为客户端
    }
    else
    {
        QMessageBox  mes;
        mes.warning(this,"Error", "请输入端口号和IP", "确定");
    }
}

void mainwindow::on_btn_disconnect_clicked()
{
    if(0 == tcp_socket->ConnectedState)
    {
        QMessageBox messbox;
        messbox.warning(this,"Error", "未连接", "确定");
        return;
    }
    if(!isserver)   //由客户端主动断开
    {
        tcp_socket_2->disconnectFromHost();
        tcp_socket_2->close();
        Reset();
    }
    else            //由服务器主动断开
    {
        tcp_socket->disconnectFromHost();
        ui->text_output->append( "断开与客户端连接");
        tcp_socket->close();
        Reset();
    }
}

void mainwindow::ButtonInit()
{
    ui->btn_choose->setEnabled(true);
    ui->btn_send->setEnabled(true);
    ui->btn_connect->setEnabled(false);
    ui->btn_disconnect->setEnabled(true);
}

void mainwindow::Reset()
{
    ui->btn_disconnect->setEnabled(false);
    ui->btn_connect->setEnabled(true);
    isserver = true;
}

void mainwindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(rect(),QPixmap("://background"));
}

