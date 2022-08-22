#include "connection.h"
#include <QDebug>
Connection::Connection(QWidget *parent = 0) : QWidget(parent) {
    tcp = new QTcpSocket(this);
    connect(tcp, &QTcpSocket::connected, this, [this] {
        qDebug() << "connected to the host";
        connected();
    });
    connect(tcp, &QTcpSocket::disconnected, this, [this]{
        qDebug() << "disconnected to the host";
        disconnected();
    });
/*    connect(tcp, &QTcpSocket::readyRead, this, [this]{
        QByteArray message = tcp->readAll();
        receivedMessage(message);
    });*/
    connect(tcp, &QTcpSocket::readyRead, this, [this]{
        readData();
    });
}

std::string Connection::trans(const QByteArray &str) {
    std::string s(str.length(), '\000');
    for (int i = 0; i < (int)str.length(); i++) {
        s[i] = str[i];
    }
    return s;
}

QByteArray Connection::trans(const std::string &str) {
    QByteArray s;
    s.resize(str.length());
    for (int i = 0; i < (int)str.length(); i++) {
        s[i] = str[i];
    }
    return s;
}

void Connection::readData() {
    static std::string s = "";
    static int dataLength = -1;
    std::string message = trans(tcp->readAll());
    if (dataLength == -1) {
        dataLength = Encoding::decode(message.substr(0, 4));
    }
    s += message;
    if ((int)s.length() >= dataLength) {
        Encoding::Data d(s);
        dataLength = -1, s.clear();
        receivedData(d);
    }
}

void Connection::connectTo(QHostAddress ip, unsigned short port) {
    tcp->connectToHost(ip, port);
}

void Connection::disconnect() {
    tcp->close();
}

void Connection::sendMessage(const QByteArray &message) {
    tcp->write(message);
    qDebug() << "send message to host";
}

void Connection::sendData(const Encoding::Data &data) {
    auto dataPack = data.splitDataPack();
    for (auto s : dataPack) {
        tcp->write(trans(s));
    }
}

Connection::~Connection() {
    delete tcp;
}
