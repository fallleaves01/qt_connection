#ifndef CONNECTION_H
#define CONNECTION_H
#include <QTcpSocket>
#include <QByteArray>
#include <QHostAddress>
#include <QWidget>
#include "./DataModel/encoding.h"

class Connection : public QWidget {
    Q_OBJECT

    QTcpSocket *tcp;
public:
    //在std::string和QByteArray之间转换的函数，用于打包成数据包过程的类型转换
    static std::string trans(const QByteArray&);
    static QByteArray trans(const std::string&);

    explicit Connection(QWidget *parent);
    ~Connection();

private slots:
    //发起一个单线程接受数据的过程，当数据接受完成后会发出信号receivedData，目前还没有处理大文件
    void readData();

public slots:
    //链接到指定ip和端口，连接失败发出信号connectingFailed，否则发出信号connected
    void connectTo(QHostAddress ip, unsigned short port);
    //终止和当前链接
    void disconnect();
    //向当前链接中的服务端发送一个经过Encoding编码的数据包
    void sendData(const Encoding::Data &data);
    //测试用函数，发送一段纯文本
    void sendMessage(const QByteArray &message);

signals:
    //连接成功
    void connected();
    //尝试连接失败
    void connectingFailed();
    //链接中断
    void disconnected();
    //成功接收到数据包data
    void receivedData(Encoding::Data data);
    //测试用函数，接收到了一段纯文本
    void receivedMessage(QByteArray message);
};

#endif // CONNECTION_H
